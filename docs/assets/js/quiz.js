(function () {
  function parseQuizTable(sourceElement) {
    const table = sourceElement.querySelector('table');

    if (!table) {
      return [];
    }

    const rows = Array.from(table.querySelectorAll('tbody tr'));

    return rows.map((row, index) => {
      const cells = row.querySelectorAll('td');

      return {
        index: index + 1,
        question: cells[0].textContent.trim(),
        options: {
          A: cells[1].textContent.trim(),
          B: cells[2].textContent.trim(),
          C: cells[3].textContent.trim(),
        },
        correct: cells[4].textContent.trim().toUpperCase(),
      };
    });
  }

  function buildQuiz(app, quizData) {
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

      ['A', 'B', 'C'].forEach((key) => {
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

    app.appendChild(form);
    app.appendChild(scoreBox);

    function clearFeedback() {
      form.querySelectorAll('.question').forEach((question) => {
        question.classList.remove('correct', 'wrong');
        question.querySelector('.feedback').textContent = '';
      });
      scoreBox.textContent = '';
    }

    function checkAnswers() {
      let score = 0;

      quizData.forEach((item) => {
        const question = form.querySelector(`[data-index="${item.index}"]`);
        const selected = form.querySelector(`input[name="q${item.index}"]:checked`);
        const feedback = question.querySelector('.feedback');

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

      const total = quizData.length;
      const percent = Math.round((score / total) * 100);
      scoreBox.textContent = `Score: ${score}/${total} (${percent}%)`;
    }

    checkButton.addEventListener('click', checkAnswers);
    resetButton.addEventListener('click', () => {
      form.reset();
      clearFeedback();
    });

    clearFeedback();
  }

  function init() {
    const app = document.getElementById('quiz-app');

    if (!app) {
      return;
    }

    const sourceUrl = app.dataset.quizSource;

    fetch(sourceUrl)
      .then((response) => response.text())
      .then((markdown) => {
        const parser = new DOMParser();
        const doc = parser.parseFromString(markdown, 'text/html');
        const sourceElement = doc.body;
        const quizData = parseQuizTable(sourceElement);

        if (!quizData.length) {
          app.textContent = 'Quiz data was not found.';
          return;
        }

        buildQuiz(app, quizData);
      })
      .catch(() => {
        app.textContent = 'Quiz data could not be loaded.';
      });
  }

  if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', init);
  } else {
    init();
  }
}());
