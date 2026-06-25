# GitHub Workflow and Progress Tracking

This setup gives you:

- A protected `main` branch for GitHub Pages and official work instructions.
- One personal branch per student.
- Short-lived work branches per exercise or part.
- Student-visible progress per exercise.
- Mentor-visible dashboard with completion percentage per student.

## 1) Keep `main` untouchable by students

Use branch protection on `main`:

1. Open repository settings in GitHub.
2. Go to branch protection rules (or rulesets).
3. Add rule for branch `main`.
4. Enable:

- Require a pull request before merging.
- Require approvals (minimum 1).
- Dismiss stale approvals on new commits.
- Include administrators.
- Restrict who can push (only you, or maintainers).

Result: pages/content built from `main` remains under your control.

## 2) Student branch model

Each student gets one branch derived from `main`:

- `student/alice`
- `student/bob`

Creation example:

```bash
git checkout main
git pull
git checkout -b student/<name>
git push -u origin student/<name>
```

Students do all work on their own branch.

## 3) Branch model inside each student branch

Recommended branch layout:

- Permanent student branch: `student/alice`
- Short-lived work branch: `alice/w2p1-uart-init`
- PR direction: `alice/w2p1-uart-init` -> `student/alice`

This means students never open normal progress PRs toward `main`.
`main` stays only for your controlled content and final integration.

## 4) Best granularity: week-part, not every tiny objective

Recommended tracking unit:

- One PR per work-instructions part: `w1p1`, `w1p2`, `w2p1`, `w2p2`, `w3p1`, `w3p2`, `w3p3`

Why this is better than objective-level tracking:

- It matches your existing course structure.
- It avoids too many branches and PRs.
- It is easier for students to understand.
- It is still fine-grained enough for meaningful percentages.

Use objective-level branches only when one part is too large. In that case, students may create several temporary branches, but only one accepted PR should count for the tracked part label.

## 5) One PR per tracked part (instead of commit message parsing)

Avoid commit-message conventions as your primary tracking source.
Use PR labels as structured data:

- `student:<name>` (example: `student:alice`)
- `exercise:<id>` (example: `exercise:w2p1`)

Tracked exercise IDs are configured in:

- `.github/progress-config.json`

Default IDs:

- `w1p1`, `w1p2`, `w2p1`, `w2p2`, `w3p1`, `w3p2`, `w3p3`

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
2. Create a short-lived branch for a tracked part.
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
- `exercise:w1p1`, `exercise:w1p2`, `exercise:w2p1`, `exercise:w2p2`, `exercise:w3p1`, `exercise:w3p2`, `exercise:w3p3`

1. Run workflow once with manual dispatch (`workflow_dispatch`) to generate the dashboard issue.
2. Share this process with students before week 1.

## Notes

- You can still enforce commit-message rules, but use them only as secondary quality checks.
- PR labels are easier to audit and automate reliably.
