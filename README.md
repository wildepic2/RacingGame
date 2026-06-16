# Racing Game
A simple racing game written in C using [raylib](https://www.raylib.com/).

## Features

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
├── src/
│   └── gameManager.c
│   └── gameManager.h
│   └── initTextures.c
│   └── initTextures.h
│   └── main.c
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

## License

This project is licensed under the terms included in the `LICENSE` file.