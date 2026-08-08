# Racing Game

A feature-rich 2D racing game written in C using [raylib](https://www.raylib.com/). Players race through custom-designed tracks with realistic physics, checkpoints, and competitive lap timing. The game includes a developer mode for map creation and customization.

[![Build and Package](https://github.com/wildepic2/RacingGame/workflows/Build%20and%20Package/badge.svg)](https://github.com/wildepic2/RacingGame/actions)

## 🎮 Features

- **Realistic Car Physics**: Smooth acceleration, coasting deceleration, and dynamic braking mechanics
- **Multiple Lap Racing**: 3-lap race mode with checkpoint tracking and finish line detection
- **Camera System**: Smooth camera following that keeps the player car centered on screen
- **Track Penalty System**: Grass tiles enforce a speed limit to add strategic depth
- **Scoring & Leaderboard**: High score tracking and persistent storage
- **Developer Map Editor**: Built-in tools to create custom tracks
  - Real-time map drawing with tile placement
  - Automatic map save/load functionality
  - Multiple tile types (road, grass, corners, start/finish lines)
  - Export maps as hardcoded strings for game distribution
- **Main Menu**: Clean UI for game selection and mode toggling
- **Game Over Screen**: Results display with high score comparison
- **Countdown Timer**: Pre-race countdown before lap timing begins
- **KMH Speedometer**: Real-time speed display during gameplay

## 🎯 Gameplay

The objective is to complete 3 laps around the track as quickly as possible. Players must:
- Navigate through checkpoints in order
- Cross the finish line to complete each lap
- Manage speed efficiently (driving on grass slows you down)
- Beat the current high score

## 📋 Project Structure

```
RacingGame/
├── .github/
│   └── workflows/
│       └── build.yml                 # CI/CD workflow for automated builds
├── assets/                           # Game sprites and graphics
│   ├── car_up.png                   # Player car sprite (upward facing)
│   ├── car_down.png                 # Player car sprite (downward facing)
│   ├── car_left.png                 # Player car sprite (left facing)
│   ├── car_right.png                # Player car sprite (right facing)
│   ├── corner_left.png              # Road tile (left corner)
│   ├── corner_left_down.png         # Road tile (left-down corner)
│   ├── corner_right.png             # Road tile (right corner)
│   ├── corner_right_down.png        # Road tile (right-down corner)
│   ├── green_ground.png             # Grass/off-road tile
│   ├── straight_road_left_right.png # Road tile (horizontal)
│   ├── straight_road_up_down.png    # Road tile (vertical)
│   ├── start_line_mark*.png         # Start line sprites (directional)
│   └── finish_line_mark*.png        # Finish line sprites (directional)
├── src/
│   ├── main.c                        # Application entry point
│   ├── state.h/c                     # Global game state management
│   ├── gameManager.h/c               # Main game loop and flow control
│   ├── playerCarManager.h/c          # Car physics, movement, and rendering
│   ├── menuManager.h/c               # Main menu and game over screens
│   ├── mapManager.h/c                # Track rendering and tile system
│   ├── mapString.h/c                 # Map data serialization
│   ├── checkpointsManager.h/c        # Checkpoint tracking system
│   ├── finishMark.h/c                # Finish line detection logic
│   ├── devMode.h/c                   # Developer map editor mode
│   ├── autoSaveMapDevMode.h/c        # Auto-save functionality for dev mode
│   ├── highscoreManager.h/c          # High score persistence
│   ├── gameOverlayText.h/c           # HUD text rendering (lap count, timer)
│   ├── countdownGameStart.h/c        # Pre-race countdown timer
│   ├── initTextures.h/c              # Texture loading and management
│   ├── errorManager.h/c              # Error handling and logging
│   └── errorManager.h                # Error state management
├── CMakeLists.txt                    # Build configuration
├── LICENSE                           # Project license
└── README.md                          # This file
```

## 🕹️ Controls

### Main Game
| Input | Action |
|-------|--------|
| **W** | Move car forward |
| **S** | Move car backward |
| **A** | Move car left |
| **D** | Move car right |
| **W+A** / **W+D** / **S+A** / **S+D** | Move diagonally |
| **Space** | Brake (hard deceleration) |
| **ESC** | Exit game |

### Main Menu
| Input | Action |
|-------|--------|
| **Left Arrow + Right Arrow** (simultaneously) | Toggle Developer Mode |
| **Select Option** | Enter game/mode |
| **ESC** | Exit |

### Developer Mode (Map Editor)
| Input | Action |
|-------|--------|
| **Up Arrow** | Previous texture tile |
| **Down Arrow** | Next texture tile |
| **P** | Place selected texture at car position |
| **F1** | Export map as string (console output) |
| **R** | Reset map to all grass |
| **WASD** | Navigate map with car |
| **Space** | Brake (for precise placement) |
| **ESC** | Exit to menu |

## 🚀 Getting Started

### Prerequisites
- CMake 4.2 or later
- C23 compatible compiler (GCC, Clang, MSVC)
- Git
- Platform-specific dependencies:
  - **Linux**: X11, OpenGL, audio libraries
  - **Windows**: Visual C++ runtime
  - **macOS**: Xcode command line tools

### Building from Source

```bash
# Clone the repository
git clone https://github.com/wildepic2/RacingGame.git
cd RacingGame

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake -B . -DCMAKE_BUILD_TYPE=Release

# Build the project
cmake --build . --config Release

# Run the game
./RacingGame
```

### Running Pre-built Binaries

Pre-compiled binaries are available in the [Releases](https://github.com/wildepic2/RacingGame/releases) section:
- **Linux**: `RacingGame-linux-v*.tar.gz`
- **Windows**: `RacingGame-windows-v*.zip`

Simply extract and run the executable. Make sure the `assets` folder is in the same directory as the executable.

## 🏗️ Architecture

### Game States
- **MAIN_MENU**: Initial menu screen with mode selection
- **PLAYING**: Active gameplay with lap tracking
- **GAME_OVER**: Results screen after completing all laps
- **ERROR_STATE**: Error handling and recovery

### Key Systems

**Physics System** (`playerCarManager.c`)
- Acceleration: 0.0959 units/frame (realistic 3-second 0-100 km/h)
- Max speed: 51.81 units/frame (~300 km/h equivalent)
- Braking: 0.1059 units/frame (hard stop)
- Coasting: 0.00508 units/frame (gradual deceleration)
- Grass penalty: Limits speed to 10 km/h

**Map System** (`mapManager.c`)
- 100x100 tile grid with 384px tile size (~38.4km × 38.4km world)
- Multiple terrain types with visual sprites
- Automatic checkpoint calculation along roads
- Camera-based rendering (only visible tiles drawn)

**Checkpoint System** (`checkpointsManager.c`)
- Automatic checkpoint placement on roads during map load
- Sequential checkpoint validation
- Lap counting tied to finish line crosses

**Persistence** (`highscoreManager.c`, `autoSaveMapDevMode.c`)
- High scores saved to local file
- Dev mode maps auto-saved during editing
- Map data stored as serialized tile strings

## 📊 Gameplay Mechanics

### Car Physics
The car accelerates realistically with three distinct phases:
1. **Acceleration** (only when pressing movement keys): +0.0959 units/frame until max speed
2. **Coasting** (when no keys pressed): -0.00508 units/frame gradual slow-down
3. **Braking** (Space key): -0.1059 units/frame hard stop

### Speed System
- Speed is calculated in game units and converted to km/h for display
- Formula: `kmh = speed × 5.79`
- Off-road (grass) has a 10 km/h max speed limit unless in Dev mode

### Lap Tracking
1. Player starts at Start Line (must cross in correct direction)
2. Must pass checkpoints in sequence
3. Completes lap when crossing Finish Line
4. Lap count increments, timer resets for next lap
5. After 3 laps, game enters Game Over state

## 🛠️ Development

### Map Editor Quick Start

1. From main menu, press **Left Arrow + Right Arrow** to toggle Dev Mode
2. Select "Play" to enter the map editor
3. Use **Up/Down arrows** to select tile type:
   - 0: Grass (green)
   - 1-8: Various road and corner tiles
   - 9-12: Start line tiles (directional)
   - 13-16: Finish line tiles (directional)
4. Use **WASD** to move around the map
5. Press **P** to place the selected tile at your car position
6. Press **F1** to export your map as a string
7. Copy the output and add it to `mapString.c` to make it a playable track

### Compile-Time Configuration

Edit constants in `playerCarManager.c`:
```c
const float accelerationSpeedFrame = 0.0959f;    // Adjust acceleration
const float brakeSpeedFrame = 0.1059f;           // Adjust brake strength
const float maxSpeed = 51.81f;                   // Max vehicle speed
const int maxGrassKMH = 10;                      // Grass speed limit
```

### Extending the Game

Common modifications:
- **Add new tile types**: Add PNG to assets, update `initTextures.c`
- **New maps**: Use Dev Mode to create and export maps
- **Difficulty modes**: Adjust physics constants or add obstacles
- **Multiplayer**: Extend state management for multiple cars
- **Sound effects**: Integrate raylib audio system

## 🐛 Known Issues & Limitations

- Single-player only (no multiplayer support)
- Fixed 100×100 map size
- No replay system
- Limited number of texture tiles
- No difficulty levels
- Dev mode must be toggled from menu (no in-game toggle)

## 🎨 Asset Credits

- **Car sprites**: Formula 1 style racing car (pixel art)
- **Track sprites**: Custom road tileset with corners and straightaways
- All assets are included in the `assets/` folder

## 📜 License

This project is licensed under the terms specified in the [`LICENSE`](LICENSE) file. See that file for details.

## 🤝 Contributing

Contributions are welcome! Please feel free to:
1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## 📝 Commit History

- **Initial Release** (Aug 2026): Core racing gameplay, map editor, physics system
- **v1.0.0+**: Check [Releases](https://github.com/wildepic2/RacingGame/releases) for latest updates

## ❓ FAQ

**Q: How do I create my own track?**
A: Use Dev Mode (Left+Right arrow from menu) to enter the map editor. Place tiles with **P**, export with **F1**, and add the map string to `mapString.c`.

**Q: Why is my car slow on grass?**
A: Grass tiles have a 10 km/h speed limit for gameplay balance. This can be changed in Dev Mode without limits.

**Q: How do I change the start/finish line direction?**
A: Export your map in Dev Mode, locate the start/finish marks in the output string, and modify the last digit (0=up, 1=down, 2=left, 3=right).

**Q: Can I play on macOS?**
A: Yes! The project uses raylib which supports macOS. Just build from source using the standard CMake process.

## 🔧 Troubleshooting

**Game won't compile:**
- Ensure CMake 4.2+ is installed: `cmake --version`
- Verify C23 compiler support
- Install platform dependencies (see Prerequisites)

**Missing assets:**
- Ensure `assets/` folder is in the same directory as the executable
- Check that PNG files are in the correct path

**Low FPS:**
- Check system performance
- Reduce map complexity in Dev Mode
- Close other applications

## 📧 Support

For issues, questions, or suggestions, please open an [Issue](https://github.com/wildepic2/RacingGame/issues) on GitHub.

---

**Happy Racing! 🏁**