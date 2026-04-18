# Raylib Starter Project

This is a simple C++ raylib starter project prepared for VS Code.

It already includes:

- `main.cpp` with a basic game loop
- a `Makefile` for building the project
- `.vscode` configuration files for build and run tasks
- a simple starter window that shows text on the screen

This project is a good starting point for CoderDojo exercises, experiments, and small games.

## Project Structure

- `main.cpp` - the main source file
- `main.exe` - the compiled Windows executable
- `Makefile` - build instructions
- `.vscode/tasks.json` - build tasks for VS Code
- `.vscode/launch.json` - debug and run configurations for VS Code
- `resources/` - place for game assets and supporting files

## How To Run The Project In VS Code

### 1. Open the project

Open the folder in VS Code.

### 2. Check raylib tools

This setup expects raylib tools to exist in these Windows paths:

- `C:/raylib/w64devkit/bin/mingw32-make.exe`
- `C:/raylib/w64devkit/bin/gdb.exe`
- `C:/raylib/raylib`

If raylib is installed in a different place, update the paths in `.vscode/tasks.json` and `.vscode/launch.json`.

### 3. Build the program

In VS Code:

- Press `Ctrl+Shift+B`
- Choose `build debug` or `build release`

### 4. Run the program

In VS Code:

- Open `main.cpp`
- Press `F5`
- Choose `Debug` or `Run`

The project will open a window with the starter message.

## How The Starter Code Works

The code in `main.cpp` is organized like this:

- `Input(float dt)` for keyboard or mouse input
- `Update(float dt)` for game logic
- `Draw()` for drawing everything on the screen
- `main()` for creating the window and running the loop

This is a clean structure for building a simple game step by step.

## Simple Git Tutorial

Git helps us save versions of our project and share changes with GitHub.

## Part 1: Basic Everyday Commands

This is the most common workflow when you already have the project and want to send your changes.

### Step 1. Pull the latest changes

```bash
git pull
```

Use this before starting work so your computer has the newest version from GitHub.

### Step 2. Check what changed

```bash
git status
```

This shows which files were changed.

### Step 3. Add files to the commit

To add all changed files:

```bash
git add .
```

To add only one file:

```bash
git add main.cpp
```

### Step 4. Create a commit

```bash
git commit -m "Update the starter project"
```

A commit is a saved version of your work with a short message.

### Step 5. Push your changes

```bash
git push
```

This sends your commit to GitHub.

### Basic Workflow Summary

```bash
git pull
git status
git add .
git commit -m "Write a short message here"
git push
```

## Part 2: Working With Branches

Branches let us work on a new feature without changing the main version right away.

### Step 1. See the current branch

```bash
git branch
```

The branch with `*` is the one you are using now.

### Step 2. Create a new branch

```bash
git branch new-feature
```

This creates a branch called `new-feature`.

### Step 3. Switch to that branch

```bash
git checkout new-feature
```

Now your work will go into that branch.

You can also do both steps at once:

```bash
git checkout -b new-feature
```

### Step 4. Make your changes

Edit files in VS Code, for example `main.cpp`.

### Step 5. Add and commit

```bash
git add .
git commit -m "Add a new feature"
```

### Step 6. Push the branch to GitHub

```bash
git push -u origin new-feature
```

The `-u` connects your local branch to the remote branch on GitHub.

After that, next time you can usually just use:

```bash
git push
```

### Step 7. Go back to main

```bash
git checkout main
```

This returns you to the main branch.

### Step 8. Update main before new work

```bash
git pull
```

## Branch Workflow Summary

```bash
git checkout main
git pull
git checkout -b new-feature
git add .
git commit -m "Add a new feature"
git push -u origin new-feature
```

## Part 3: Pull Request Mini Tutorial

A pull request, often called a PR, is a way to ask for your branch changes to be added into `main`.

This is useful because:

- your work stays separate until it is ready
- other people can read your changes
- a teacher, teammate, or friend can review your code before merging

### Step 1. Make sure your branch is pushed

If you already worked on your feature branch, push it to GitHub:

```bash
git push -u origin new-feature
```

### Step 2. Open the repository on GitHub

Go to your project page on GitHub in the browser.

GitHub will often show a button like:

- `Compare & pull request`

Click it.

### Step 3. Check the branch direction

Make sure GitHub shows:

- base branch: `main`
- compare branch: `new-feature`

This means:

- `main` is the branch you want to update
- `new-feature` is the branch with your new work

### Step 4. Write a title and short description

Example title:

- `Add player movement`

Example description:

- `This PR adds simple keyboard movement for the player.`

Keep it short and clear.

### Step 5. Create the pull request

Click:

- `Create pull request`

Now your pull request is ready for review.

### Step 6. Merge the pull request

When the code looks good, click:

- `Merge pull request`

Then confirm the merge on GitHub.

After that, the changes from `new-feature` become part of `main`.

### Step 7. Update your local `main`

After the PR is merged, go back to your computer and run:

```bash
git checkout main
git pull
```

This brings your local `main` up to date.

## Pull Request Workflow Summary

```bash
git checkout -b new-feature
git add .
git commit -m "Add a new feature"
git push -u origin new-feature
```

Then on GitHub:

- open the repository
- click `Compare & pull request`
- check `main` <- `new-feature`
- write a title and description
- click `Create pull request`
- review and merge

## Helpful Git Commands

### See commit history

```bash
git log --oneline
```

### See all branches

```bash
git branch
```

### See changed files

```bash
git status
```

## Beginner Tips

- Pull before you start working
- Write short and clear commit messages
- Use branches for new features or experiments
- Check `git status` often
- Push your work so it is saved online too

## Example Commit Messages

- `git commit -m "Fix player movement"`
- `git commit -m "Add background color"`
- `git commit -m "Start enemy class"`
- `git commit -m "Clean up main loop"`

## Next Ideas For This Project

- move a shape with the keyboard
- draw textures from the `resources` folder
- add a player and enemies
- create score and timer systems
- experiment with collisions and sounds
