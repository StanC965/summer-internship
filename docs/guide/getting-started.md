# Getting Started

Use this checklist to set up your environment and start contributing quickly.

1. Clone this project
	 - Copy the repository URL from your Git hosting page.
	 - Clone the project to your local machine:
		 ```bash
		 git clone https://github.com/StanC965/summer-internship.git
		 ```
	 - Move into the project folder:
		 ```bash
		 cd summer-internship
		 ```
	 - Verify the repo is connected correctly:
		 ```bash
		 git remote -v
		 ```

2. Install required tools
	 - Install Git (for version control).
	 - Install Python and pip (for documentation tooling).
	 - Install dependencies listed in this repository:
		 ```bash
		 pip install -r requirements.txt
		 ```
	 - Install IAR Embedded Workbench and AVR toolchain support as described in the setup guide.
	 - Continue with the detailed setup steps in [Setup IAR Embedded Workbench Tool](setup-iar.md).

3. Review the Git workflow
	 - Read the workflow guide to understand branch naming, commits, and pull request expectations.
	 - Use only `student` branches for your tasks.
	 - See [GitHub Workflow Progress](github-workflow-progress.md) for the expected process.

4. Create a new project in IAR
	 - Open IAR and create a new workspace/project.
	 - Select the correct target device and project template.
	 - Configure build options (include paths, linker settings, output format).
	 - Build once to verify the toolchain is configured correctly.
	 - Follow the full walkthrough in [New Project in IAR](new-project-iar.md).
