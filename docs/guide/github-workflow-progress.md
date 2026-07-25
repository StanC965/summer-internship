# GitHub Workflow and Progress Tracking

This setup gives you:

- A protected `main` branch for GitHub Pages and official work instructions.
- One personal branch per student.
- Short-lived work branches per exercise or part.
- Student-visible progress per exercise.
- Mentor-visible dashboard with completion percentage per student.

## 1) Keep `main` untouchable by students

Pages/content built from `main` remains under instructor control.  
Branch `main` will be blocked from writing to it.

## 2) Student branch model

Each student gets his own branch derived from `main` (instructor will derive it):

- `student/alice`
- `student/bob`

Work example:

```bash
git checkout main
git pull
git checkout -b student/<name>
git push -u origin student/<name>
```

Students do all work on their own branch.

## 3) Branch model inside each student branch

For working on a goal, student will derive a branch out of his own.
Recommended branch layout:

- Permanent student branch: `student/alice`
- Short-lived working branch per goal: `alice/w2g1-uart-init`
- PR direction will be: from `alice/w2g1-uart-init` -> to -> `student/alice`

This means students never open normal progress PRs toward `main`.
`main` stays only for instructor controlled content and final integration.

## 4) Best granularity: week-goal, not every tiny objective

Recommended tracking unit:

- One PR per work-instructions goal: `w1g1`, `w1g2`, `w2g1`, `w2g2`, `w3g1`, `w3g2`, `w3g3`

Why this is better than objective-level tracking:

- It matches your existing course structure.
- It avoids too many branches and PRs.
- It is easier for students to understand.
- It is still fine-grained enough for meaningful percentages.

Use objective-level branches only when one goal is too large. In that case, students may create several temporary branches, but only one accepted PR should count for the tracked goal label.

## 5) One PR per tracked goal (instead of commit message parsing)

Avoid commit-message conventions as your primary tracking source.
Use PR labels as structured data:

- `student:<name>` (example: `student:alice`)
- `exercise:<id>` (example: `exercise:w2g1`)

Tracked exercise IDs are configured in:

- `.github/progress-config.json`

Default IDs:

- `w1g1`, `w1g2`, `w2g1`, `w2g2`, `w3g1`, `w3g2`, `w3g3`

Use the PR template in:

- `.github/pull_request_template.md`

This is less error-prone than free-form commit comments.

## 6) Automatic progress dashboard in GitHub

A workflow updates one GitHub Issue with progress percentages.

Workflow file:

- `.github/workflows/progress-dashboard.yml`

How it works:

1. On PR updates/merge, plus weekly schedule, workflow runs.
2. It reads `.github/progress-config.json`.
3. It scans merged PRs into `student/*` branches.
4. It computes completed exercises per student from labels.
5. It creates or updates issue titled `Work Progress Dashboard` with a table.

Table fields:

- Completed count (done/total)
- Percent complete
- Missing exercises

This gives each student a clear status and gives you one centralized overview.

## 7) Student and mentor usage

Student:

1. Keep own permanent branch `student/<name>`.
2. Create a short-lived branch for a tracked goal.
3. Open PR from the short-lived branch into `student/<name>`.
4. Add both required labels.
5. Check dashboard issue for own percentage and missing exercises.

Mentor:

1. Review PR quality as usual.
2. Merge only accepted work into the student's student branch.
3. Open dashboard issue anytime to see cohort progress.

## 8) Initial setup checklist

1. Update `.github/progress-config.json` with real student names.
2. Keep `studentBranchPrefix` as `student/` unless you rename your student branches.
3. Create labels in GitHub UI:

- `student:alice`, `student:bob`, ...
- `exercise:w1g1`, `exercise:w1g2`, `exercise:w2g1`, `exercise:w2g2`, `exercise:w3g1`, `exercise:w3g2`, `exercise:w3g3`

1. Run workflow once with manual dispatch (`workflow_dispatch`) to generate the dashboard issue.
2. Share this process with students before week 1.

## Notes

- You can still enforce commit-message rules, but use them only as secondary quality checks.
- PR labels are easier to audit and automate reliably.
