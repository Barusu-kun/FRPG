# FRPG

FRPG (Fun Retro RPG) is a small C-based role-playing game project. This repository contains the game's source code, assets, and build scripts. This README explains how to build, run, and contribute to the project.

If this README doesn't match the repository layout or build steps, update the sections below (paths, commands, dependencies) to match your codebase.

## Features

- Turn-based RPG mechanics
- Character progression and inventory
- Simple text-based UI (or minimal graphical UI depending on implementation)
- Designed for learning and experimentation in C

## Requirements

- A C compiler (GCC or Clang)
- make (recommended if a Makefile is included)
- Optional libraries depending on implementation:
  - ncurses (for terminal UI)
  - SDL2 (for simple graphics)

Check the source or build scripts for actual dependencies.

## Build

If the repository includes a Makefile, build with:

```bash
make
```

If no Makefile exists, build manually. Example (adjust paths and libraries as needed):

```bash
gcc -Wall -Wextra -Werror -std=c99 main.c game.c player.c map.c physics.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o game

```

## Run

After building, run the executable:

```bash
./game
```


## Project layout

- ./FRPG ##All in one xd

## Contributing

Indications are welcome : )

## License

No license specified. To make this project open source, add a LICENSE file (for example, MIT, Apache-2.0, or GPL-3.0) and update this section.

## Contact

If you have questions or ideas, open an issue or contact the repository owner.
