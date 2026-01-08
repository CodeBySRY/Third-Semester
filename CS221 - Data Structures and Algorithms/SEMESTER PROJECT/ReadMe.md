# Managing Nested Git Repositories (Using Git Bash)

This document explains how to create a Git repository from an **existing local folder** using **Git Bash**, while ensuring that any **nested repository inside it is ignored and not pushed** to GitHub.  
This is a common scenario when a parent folder contains coursework, and one subfolder already has its **own independent Git repository**.

---

## Scenario Overview

- I had a main folder (e.g., `3rd Semester`) that I wanted to push to GitHub.
- Inside this folder, one subfolder (e.g., `SEMESTER PROJECT`) was **already a Git repository**.
- Therefore, I wanted:
  - The **parent folder** to be a GitHub repository
  - The **nested repository** to remain independent
  - The nested repository **not to be tracked or pushed** as part of the parent repository

---

## Important Git Rule (Must Know)

> **Git does NOT support repositories inside repositories (nested repos).**

If a nested repo is not handled properly, Git will:
- Either treat it as a broken submodule
- Or refuse to track it correctly
- Or accidentally push `.git` metadata (bad practice)

---

## Correct and Recommended Solution

### ✔️ Ignore the Nested Repository Completely

This keeps:
- The parent repo clean
- The nested repo independent
- Git behavior predictable and professional

---

## Step-by-Step Guide (Git Bash)

### Step 1 — Open Git Bash

Open **Git Bash** manually from your system (Run As Administrator).

Navigate to the parent folder (example):

```bash
cd /e/"home"/"Documents"/"3rd Semester"
```
### Step 2 — Initialize Git in the Parent Folder
```bash
git init
```


This creates a .git folder for the parent repository.

### Step 3 — Create or Edit .gitignore

Create a `.gitignore` file if it does not exist:

```bash
touch .gitignore
```



Open it in any editor and explicitly ignore the nested repository folder.
If you want to open it in notepad:
```bash
notepad .gitignore
```
Once the notepad is opened, then type the following command into the notepad, save, and exit:

```txt
CS221 - Data Structures and Algorithms/SEMESTER PROJECT/
```


This ensures:

- The nested repo is not tracked
- Its internal .git folder is ignored
- No conflicts occur

### Step 4 — Verify Ignoring Behavior

Run:
```bash
git status
```

You should see:

- The main course folders listed as untracked
- ❌ The nested repository NOT listed

If the nested repo still appears:

- Double-check the folder name
- Ensure the path in .gitignore is correct

### Step 5 — Stage and Commit Parent Repository
```bash
git add .
git commit -m "Add Third Semester coursework"
```

### Step 6 — Link to GitHub Repository

Create an empty repository on GitHub first.  
Then link it:

```bash
git remote add origin https://github.com/USERNAME/REPO_NAME.git
```


**Verify**:
```bash
git remote -v
```

### Step 7 — Push to GitHub
```bash
git branch -M main
git push -u origin main
```