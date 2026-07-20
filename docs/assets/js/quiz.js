(function () {
  const STORAGE_KEY = 'summerInternshipQuizAttempts';
  const CLIENT_ID_KEY = 'summerInternshipQuizClientId';

  function getClientId() {
    try {
      const existing = localStorage.getItem(CLIENT_ID_KEY);
      if (existing) {
        return existing;
      }

      const id = `client-${Date.now()}-${Math.random().toString(36).slice(2, 10)}`;
      localStorage.setItem(CLIENT_ID_KEY, id);
      return id;
    } catch (error) {
      return `client-${Date.now()}`;
    }
  }

  function getQuizId(app) {
    return app.dataset.quizId || window.location.pathname;
  }

  function getQuizTitle(app) {
    return app.dataset.quizTitle || document.title || 'Quiz';
  }

  function loadAttempts() {
    try {
      const raw = localStorage.getItem(STORAGE_KEY);
      const parsed = raw ? JSON.parse(raw) : [];
      return Array.isArray(parsed) ? parsed : [];
    } catch (error) {
      return [];
    }
  }

  function saveAttempt(attempt) {
    const attempts = loadAttempts();
    attempts.push(attempt);
    localStorage.setItem(STORAGE_KEY, JSON.stringify(attempts));
  }

  function getAttemptsForQuiz(quizId) {
    return loadAttempts().filter((attempt) => attempt.quizId === quizId);
  }

  function sendFirstAttemptToEndpoint(app, payload) {
    const endpoint = app.dataset.submitEndpoint;

    if (!endpoint) {
      return;
    }

    const body = JSON.stringify(payload);

    try {
      // sendBeacon is resilient during navigation and works well for fire-and-forget logging.
      if (navigator.sendBeacon) {
        const blob = new Blob([body], { type: 'application/json' });
        navigator.sendBeacon(endpoint, blob);
        return;
      }
    } catch (error) {
      // Fall through to fetch.
    }

    // no-cors keeps this simple for static hosting and Google Apps Script web app endpoints.
    fetch(endpoint, {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      mode: 'no-cors',
      body,
    }).catch(() => {
      // Ignore network errors; local score storage remains the source of truth for the learner.
    });
  }

  function renderQuizStats(statsBox, quizId) {
    const attempts = getAttemptsForQuiz(quizId);

    if (!attempts.length) {
      statsBox.textContent = 'No attempts recorded yet.';
      return;
    }

    const best = attempts.reduce((max, item) => Math.max(max, item.percent), 0);
    const latest = attempts[attempts.length - 1];

    statsBox.textContent = `Attempts: ${attempts.length}. Latest: ${latest.percent}%. Best: ${best}%`;
  }

  function parseQuizTable(sourceElement) {
    const table = sourceElement.querySelector('table');

    if (!table) {
      return [];
    }

    const headerCells = Array.from(table.querySelectorAll('thead th'));
    const optionKeys = headerCells
      .slice(1, -1)
      .map((cell) => cell.textContent.trim().toUpperCase())
      .filter((key) => key);

    if (!optionKeys.length) {
      return [];
    }

    const rows = Array.from(table.querySelectorAll('tbody tr'));

    return rows.map((row, index) => {
      const cells = row.querySelectorAll('td');
      const options = {};

      optionKeys.forEach((key, optionIndex) => {
        const cell = cells[optionIndex + 1];
        options[key] = cell ? cell.textContent.trim() : '';
      });

      return {
        index: index + 1,
        question: cells[0].textContent.trim(),
        options,
        optionKeys,
        correct: cells[cells.length - 1].textContent.trim().toUpperCase(),
      };
    });
  }

  function buildQuiz(app, quizData) {
    const quizId = getQuizId(app);
    const quizTitle = getQuizTitle(app);

    app.innerHTML = '';

    const form = document.createElement('form');
    form.className = 'quiz-form';

    quizData.forEach((item) => {
      const section = document.createElement('section');
      section.className = 'question';
      section.dataset.index = String(item.index);
      section.dataset.correct = item.correct;

      const heading = document.createElement('h2');
      heading.textContent = `${item.index}. ${item.question}`;
      section.appendChild(heading);

      item.optionKeys.forEach((key) => {
        const label = document.createElement('label');
        label.className = 'option';

        const input = document.createElement('input');
        input.type = 'radio';
        input.name = `q${item.index}`;
        input.value = key;

        label.appendChild(input);
        label.appendChild(document.createTextNode(` ${key}. ${item.options[key]}`));
        section.appendChild(label);
        section.appendChild(document.createElement('br'));
      });

      const feedback = document.createElement('p');
      feedback.className = 'feedback';
      section.appendChild(feedback);

      form.appendChild(section);
    });

    const actions = document.createElement('div');
    actions.className = 'quiz-actions';

    const checkButton = document.createElement('button');
    checkButton.type = 'button';
    checkButton.id = 'check-answers';
    checkButton.textContent = 'Check answers';

    const resetButton = document.createElement('button');
    resetButton.type = 'button';
    resetButton.id = 'reset-quiz';
    resetButton.textContent = 'Reset';

    actions.appendChild(checkButton);
    actions.appendChild(resetButton);
    form.appendChild(actions);

    const scoreBox = document.createElement('div');
    scoreBox.className = 'score-box';
    scoreBox.setAttribute('aria-live', 'polite');

    const statsBox = document.createElement('div');
    statsBox.className = 'stats-box';
    statsBox.setAttribute('aria-live', 'polite');

    app.appendChild(form);
    app.appendChild(scoreBox);
    app.appendChild(statsBox);

    function clearFeedback() {
      form.querySelectorAll('.question').forEach((question) => {
        question.classList.remove('correct', 'wrong');
        question.querySelector('.feedback').textContent = '';
      });
      scoreBox.textContent = '';
    }

    function checkAnswers() {
      let score = 0;
      let gradableCount = 0;

      quizData.forEach((item) => {
        const question = form.querySelector(`[data-index="${item.index}"]`);
        const selected = form.querySelector(`input[name="q${item.index}"]:checked`);
        const feedback = question.querySelector('.feedback');
        const hasAnswerKey = item.optionKeys.includes(item.correct);

        if (!hasAnswerKey) {
          question.classList.remove('correct', 'wrong');
          feedback.textContent = 'No answer key provided for this question.';
          return;
        }

        gradableCount += 1;

        if (selected && selected.value === item.correct) {
          score += 1;
          question.classList.add('correct');
          question.classList.remove('wrong');
          feedback.textContent = 'Correct';
          return;
        }

        question.classList.add('wrong');
        question.classList.remove('correct');
        feedback.textContent = `Wrong. Correct answer: ${item.correct}. ${item.options[item.correct]}`;
      });

      const total = gradableCount;
      const percent = total > 0 ? Math.round((score / total) * 100) : 0;
      const attemptsBefore = getAttemptsForQuiz(quizId).length;
      if (total > 0) {
        scoreBox.textContent = `Score: ${score}/${total} (${percent}%)`;
      } else {
        scoreBox.textContent = 'Practice mode: this quiz has no answer keys configured yet.';
      }

      const attempt = {
        quizId,
        quizTitle,
        score,
        total,
        percent,
        timestamp: new Date().toISOString(),
      };

      saveAttempt(attempt);

      if (attemptsBefore === 0) {
        sendFirstAttemptToEndpoint(app, {
          event: 'first_attempt',
          clientId: getClientId(),
          page: window.location.href,
          userAgent: navigator.userAgent,
          ...attempt,
        });
      }

      renderQuizStats(statsBox, quizId);
    }

    checkButton.addEventListener('click', checkAnswers);
    resetButton.addEventListener('click', () => {
      form.reset();
      clearFeedback();
      renderQuizStats(statsBox, quizId);
    });

    clearFeedback();
    renderQuizStats(statsBox, quizId);
  }

  function formatDate(isoDate) {
    const date = new Date(isoDate);

    if (Number.isNaN(date.getTime())) {
      return isoDate;
    }

    return date.toLocaleString();
  }

  function renderResultsPage(app) {
    const attempts = loadAttempts();
    app.innerHTML = '';

    if (!attempts.length) {
      app.textContent = 'No quiz attempts found yet. Complete a quiz first.';
      return;
    }

    const byQuiz = attempts.reduce((acc, attempt) => {
      if (!acc[attempt.quizId]) {
        acc[attempt.quizId] = [];
      }
      acc[attempt.quizId].push(attempt);
      return acc;
    }, {});

    const cards = document.createElement('div');
    cards.className = 'results-cards';

    Object.keys(byQuiz).forEach((quizId) => {
      const quizAttempts = byQuiz[quizId];
      const latest = quizAttempts[quizAttempts.length - 1];
      const best = quizAttempts.reduce((max, item) => Math.max(max, item.percent), 0);
      const avg = Math.round(
        quizAttempts.reduce((sum, item) => sum + item.percent, 0) / quizAttempts.length
      );

      const card = document.createElement('section');
      card.className = 'result-card';

      const heading = document.createElement('h2');
      heading.textContent = latest.quizTitle || quizId;
      card.appendChild(heading);

      const summary = document.createElement('p');
      summary.textContent = `Attempts: ${quizAttempts.length} | Latest: ${latest.percent}% | Best: ${best}% | Average: ${avg}%`;
      card.appendChild(summary);

      cards.appendChild(card);
    });

    const table = document.createElement('table');
    table.className = 'attempts-table';

    const header = document.createElement('thead');
    header.innerHTML = '<tr><th>Date</th><th>Quiz</th><th>Score</th><th>Percent</th></tr>';
    table.appendChild(header);

    const body = document.createElement('tbody');
    attempts
      .slice()
      .sort((a, b) => new Date(b.timestamp).getTime() - new Date(a.timestamp).getTime())
      .forEach((attempt) => {
        const row = document.createElement('tr');
        row.innerHTML = `<td>${formatDate(attempt.timestamp)}</td><td>${attempt.quizTitle || attempt.quizId}</td><td>${attempt.score}/${attempt.total}</td><td>${attempt.percent}%</td>`;
        body.appendChild(row);
      });

    table.appendChild(body);

    const resetButton = document.createElement('button');
    resetButton.type = 'button';
    resetButton.id = 'reset-results';
    resetButton.textContent = 'Clear all recorded quiz progress';
    resetButton.addEventListener('click', () => {
      localStorage.removeItem(STORAGE_KEY);
      renderResultsPage(app);
    });

    app.appendChild(cards);
    app.appendChild(table);
    app.appendChild(resetButton);
  }

  function init() {
    const quizApp = document.getElementById('quiz-app');
    const resultsApp = document.getElementById('quiz-results-app');

    if (resultsApp) {
      renderResultsPage(resultsApp);
    }

    if (!quizApp) {
      return;
    }

    const sourceUrl = quizApp.dataset.quizSource;

    if (!sourceUrl) {
      const inlineSource = document.getElementById('quiz-source') || document;
      const quizData = parseQuizTable(inlineSource);

      if (!quizData.length) {
        quizApp.textContent = 'Quiz data was not found.';
        return;
      }

      buildQuiz(quizApp, quizData);
      return;
    }

    fetch(sourceUrl)
      .then((response) => response.text())
      .then((markdown) => {
        const parser = new DOMParser();
        const doc = parser.parseFromString(markdown, 'text/html');
        const sourceElement = doc.body;
        const quizData = parseQuizTable(sourceElement);

        if (!quizData.length) {
          quizApp.textContent = 'Quiz data was not found.';
          return;
        }

        buildQuiz(quizApp, quizData);
      })
      .catch(() => {
        quizApp.textContent = 'Quiz data could not be loaded.';
      });
  }

  if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', init);
  } else {
    init();
  }
}());
