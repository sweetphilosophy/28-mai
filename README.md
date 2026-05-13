# C++ Advanced End Of Year Game Project

This is a C++ raylib project prepared for the end of the year of the C++ Advanced course

The project currently contains:

- a `Game` class that controls the main game loop
- a player with movement, jumping, gravity, and collision
- a camera that follows the player
- a map loaded from a PNG image
- a simple creative mode for editing tiles

## Project Structure

- `main.cpp` - the small entry point that creates and runs the game
- `include/` - header files with class and function declarations
- `src/` - C++ implementation files
- `assets/` - images and other game assets
- `assets/misc/Dimension0.png` - the current map image
- `Makefile` - build instructions
- `.vscode/tasks.json` - build tasks for VS Code
- `.vscode/launch.json` - debug and run configurations for VS Code
- `bin/` - compiled program output
- `obj/` - temporary build files

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

The project will open a raylib window with the current tile map and player.

## How The Code Works So Far

This section explains the code in a simple order.

### 1. The Program Starts In `main.cpp`

`main.cpp` is intentionally very small:

```cpp
Game game;
game.run();
```

It creates one `Game` object, then asks it to run.

That means most of the project starts from the `Game` class.

### 2. `Game` Controls The Main Loop

The main game code is split between:

- `include/Game.h`
- `src/Game.cpp`

`Game::run()` does three big things:

1. Creates the game window.
2. Creates the camera.
3. Repeats the game loop until the player closes the window.

The loop has this order every frame:

```cpp
Input(dt, cameraManager);
Update(dt, cameraManager);
Draw();
```

Think of one frame like this:

- `Input` asks: what did the player press?
- `Update` asks: what should change?
- `Draw` asks: what should appear on screen?

This pattern is very common in games.

### 3. `Config.h` Stores Shared Settings

`include/Config.h` contains values used in many files.

Examples:

- tile size: `tileWidth` and `tileHeight`
- screen size: `SCREEN_WIDTH` and `SCREEN_HEIGHT`
- physics values: `gravity` and `jumpVelocity`
- tile IDs: `Air`, `Dirt`, `Grass`, `Stone`, and others

If you want to change basic game rules, this is often a good file to check first.

### 4. The Map Is Called A `Dimension`

The map code is in:

- `include/DimensionManager.h`
- `src/DimensionManager.cpp`

A `Dimension` is one tile map.

When the game starts, this file is loaded:

```text
assets/misc/Dimension0.png
```

Each pixel in the PNG becomes one tile in the game.

For example:

- white pixel means `Air`
- brown pixel means `Dirt`
- green pixel means `Grass`
- gray pixel means `Stone`

The map is stored as a 2D vector:

```cpp
tiles[y][x]
```

That means:

- `y` is the row
- `x` is the column

The map can also be saved back into a PNG file.

### 5. `DimensionManager` Chooses The Active Map

`DimensionManager` stores all dimensions in a list.

Right now, the game mainly uses one active dimension.

The active dimension is the one that gets:

- updated
- drawn
- checked for player collision

Later, this system could be used for multiple worlds, levels, or dimensions.

### 6. `ObjectManager` Owns Game Objects

The object code is in:

- `include/ObjectManager.h`
- `src/ObjectManager.cpp`

Right now, `ObjectManager` owns the player.

It sets the player's starting values:

- health
- damage
- speed
- starting position
- hitbox size

During the game loop, `ObjectManager` sends input and update calls to the player.

### 7. Entities Are Things That Can Exist In The World

The entity code is in:

- `include/Entity.h`
- `src/Entity.cpp`

`Entity` is a base class.

It stores common data such as:

- health
- speed
- movement direction
- hitbox
- ID

It also has helper functions for collision with tiles.

The important idea is:

> Shared behavior goes in `Entity`, and more specific behavior goes in child classes.

### 8. `GroundEntity` Adds Gravity And Jumping

The ground entity code is in:

- `include/GroundEntity.h`
- `src/GroundEntity.cpp`

`GroundEntity` inherits from `Entity`.

It adds:

- gravity
- vertical velocity
- jumping
- landing on tiles
- bumping into walls or ceilings

The player uses this class because the player walks and jumps on the ground.

### 9. `Player` Handles Player Controls

The player code is in:

- `include/Player.h`
- `src/Player.cpp`

The player currently supports:

- `A` to move left
- `D` to move right
- `Space` to jump
- `C` to toggle creative mode
- mouse wheel to choose a tile in creative mode
- left click to remove a tile in creative mode
- right click to place the selected tile in creative mode
- `Ctrl+S` to save the current map

The player does not directly change a tile immediately.

Instead, it adds an `Action` to the dimension's `updateQueue`.

Then the dimension processes a few queued updates each frame.

### 10. `CameraManager` Follows The Player

The camera code is in:

- `include/CameraManager.h`
- `src/CameraManager.cpp`

The camera follows the center of the player's hitbox.

It also:

- keeps the view centered on the screen
- limits how far up or down the camera can move
- converts mouse screen position into world position

That last part is important for creative mode, because the mouse clicks on the screen but tiles exist in the game world.

### 11. Drawing Uses World Space And Screen Space

In `Game::Draw()`, there are two drawing areas.

Inside `BeginMode2D(cameraManager.GetCamera())`:

- draw the map
- draw the player
- draw things that exist in the game world

After `EndMode2D()`:

- draw UI text
- draw things that stay fixed on the screen

The creative mode text is screen UI, so it is drawn after `EndMode2D()`.

### 12. Useful Debug And Test Controls

- `F11` toggles fullscreen.
- `Tab` toggles tile ID text on the map.
- `C` toggles creative mode.
- `Ctrl+S` saves the edited map.

These controls are helpful while building and testing the game.

## Good First Files To Read

If you are new to the project, this reading order is recommended:

1. `main.cpp`
2. `include/Game.h`
3. `src/Game.cpp`
4. `include/Config.h`
5. `include/Player.h`
6. `src/Player.cpp`
7. `include/DimensionManager.h`
8. `src/DimensionManager.cpp`

Start with the big flow first, then read the details.

## Ideas To Try

Good first changes could be:

- change the player's speed
- change jump height
- add a new tile color and tile ID
- change the player's starting position
- draw the player with a filled rectangle instead of only debug lines
- add a new key for a simple action
- add another map image

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