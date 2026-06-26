# Racing Game
A simple racing game written in C using [raylib](https://www.raylib.com/).

## Features
- Menu
- dev mode (map creator)
- Auto save map in dev mode what you made
- Realistic Acceleration and Braking

## Project Structure

```text
RacingGame/
├── .github/
│   └── workflows/
│       └── build.yml
├── assets/
│   └── Formula 1 car and trackset/
│   └── car_up.png
│   └── car_down.png
│   └── car_left.png
│   └── car_right.png
│   └── corner_left.png
│   └── corner_left_down.png
│   └── corner_right.png
│   └── corner_right_down.png
│   └── green_ground.png
│   └── straight_road_left_right.png
│   └── straight_road_up_down.png
├── src/
│   └── autoSaveMapDevMode.c
│   └── autoSaveMapDevMode.h
│   └── gameManager.c
│   └── gameManager.h
│   └── initTextures.c
│   └── initTextures.h
│   └── main.c
│   └── mapManager.c
│   └── mapManager.h
│   └── mapString.c
│   └── mapString.h
│   └── menuManager.c
│   └── menuManager.h
│   └── playerCarManager.c
│   └── playerCarManager.h
│   └── state.c
│   └── state.h
├── CMakeLists.txt
└── README.md
└── LICENSE
```

## Controls
- **WASD** to controll the direction of the car.
    * **WA** **WD** **SA** **SD** to move the car diagonally.
- **Space** to brake the car.
- **LEFT-RIGHT Arrow at same time in menu** to activate DEV mode.
- **ESC** to exit the game.
######      DEV mode
- **UP-Down Arrays** to select the Texture ID you want.
- **P** to draw the selected Texture ID on the dev mode map.
- **F1** to export the dev mode map as an map string hardcodable into the code to add your map
- **R** to reset the dev mode map to grass.

## License

This project is licensed under the terms included in the `LICENSE` file.