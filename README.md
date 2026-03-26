# Steps Design Project

This project contains my STEPS senior design implementation with my team, including the core components for input tiles, master control, and the rhythm game. It is designed to showcase interactive rhythm-based gameplay and tile input mechanics.

## Project Structure

The repository contains the following main files:

- **Input Tile Files**  
  Handles tile creation, input detection, and interaction logic.
  - `input_tile.ino` (or relevant file names) – defines the behavior of individual tiles when pressed or activated.

- **Master Files**  
  Coordinates the overall game logic, manages states, scoring, and timing.
  - `master.ino` – main game controller that handles initialization, game loop, and score tracking.

- **Rhythm Game Files**  
  Implements the rhythm-based gameplay, including song timing, tile sequences, and animations.  
  (Contains ~50 files; all located in the `rhythm-game` folder)*
  - `rhythm-game/` – folder with all rhythm game components, including:
    - Song data
    - Animation handlers
    - Game state management
    - Audio handling

## How to Run

1. Ensure all dependencies (if any) are installed.
2. Open `master.ino` in your preferred environment to start the game.
3. The input tiles will respond to your interactions, synced with the rhythm game mechanics.

## Notes

- Each component is modular and can be extended for additional functionality, such as adding new songs or tile effects.
- The rhythm game folder contains multiple interdependent files; please do not rename or move files to avoid breaking the game.
