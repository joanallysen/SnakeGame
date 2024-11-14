# Snake Game in C++ (Console-based) 🐍

A simple yet fun **Snake Game** built using C++ for the console. This game allows both **single-player** and **multiplayer** modes, where two players can play on the same screen using different controls. Think like playing the flashgame fireboy and watergirl, although controls are different.

## Features

- **Single-player mode**: Classic Snake gameplay where the player controls a snake and eats food to grow longer.
- **Multiplayer mode**: Two players can play simultaneously on the same screen, each controlling a separate snake, trying to defeat the other snake by trapping them!
- **Settings menu**: Customize game options like screen size, speed, and wall border size.
- **Continuous growth**: Custom mode such as tail growing continuously after some time without eating the fruit, adding to the challenge.
- **Customizable game rules**: You can turn on/off death upon hitting the wall, change the snake's speed, or adjust the size of the game panel.

## Gameplay

### Controls:
- **Player 1** (Snake 1):
  - `W` - Move Up
  - `A` - Move Left
  - `S` - Move Down
  - `D` - Move Right
  - `X` - Quit Game
  
- **Player 2** (Snake 2 - Multiplayer only):
  - `I` - Move Up
  - `J` - Move Left
  - `K` - Move Down
  - `L` - Move Right

Unfortunately due to current input delay, the original input for player 2 using the arrow key is momentarily replaced with 'I' 'J' 'K' 'L'.

### General Objective:
- Eat the food (`#`) to grow longer.
- Avoid running into walls or your own tail (depending on the settings).
- In multiplayer, try to avoid hitting the other player's tail or hit the wall!

---

## How to Play

1. **Start the Game**: On launching, you will be presented with a **main menu** where you can choose to play **Single-player** or **Multiplayer**.
   
2. **Settings**: You can adjust game settings, including screen size, snake speed, and whether you die when hitting the wall.

3. **Gameplay**: Use the controls to guide your snake to eat food and grow. In multiplayer mode, each player will control their own snake with different keys.

4. **End Game**: The game ends when a player hits a wall or their own tail (or the opponent’s tail in multiplayer).

5. **Play Again**: After a game ends, you'll be given an option to play again.

---

## Installation

### Prerequisites

- C++ Compiler (e.g., **g++** or **MSVC**).
- **Windows OS** (since this game uses Windows-specific libraries like `windows.h` and `conio.h`).

### Steps to Compile & Run

1. **Clone the repository**:

   ```bash
   git clone https://github.com/joanallysen/SnakeGame.git
   ```

2. **Navigate to the project directory**:

   ```bash
   cd SnakeGame
   ```

3. **Compile the code**:

   For **g++**:
   ```bash
   g++ -o snakegame main.cpp
   ```

   For **MSVC**:
   - Open the project in Visual Studio, then build and run the program.

4. **Run the game**:

   ```bash
   ./snakegame
   ```
---

## Screenshots

![Game Screenshot](link-to-your-screenshot.png)

---

## Settings Menu

You can modify these game settings:

1. **Game Panel Size**: Adjust the width and height of the game board (keep in mind, larger sizes might cause screen issues).
2. **Snake Speed**: Set how fast the snake moves.
3. **Death on Wall**: Enable or disable dying when hitting a wall.
4. **Tail Growth**: Enable or disable continuous tail growth over time (only in multiplayer).

---

## Game Rules

- **Wall Collision**: If enabled, hitting the wall results in a game over for the player.
- **Tail Collision**: Colliding with your own or the opponent’s tail will result in a game over.
- **Fruit**: The fruit appears randomly on the board. Eating it will increase your score and the length of your snake.

---

## Contributing

If you would like to contribute to the project, feel free to fork the repository and submit a pull request. Any improvements, bug fixes, or new features are welcome!

---

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

## Acknowledgements

- **C++**: For powering the game logic and rendering.
- **conio.h**: For handling keyboard input in the console.
- **windows.h**: For controlling the console cursor position.
  
---

Feel free to adjust this `README.md` with more specific details about your game or additional features you've added!
