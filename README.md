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
# compile all .c files in src/ into an executable named frpg
gcc -std=c11 -Wall -Wextra -O2 -Iinclude -o frpg src/*.c
# if using ncurses or SDL2, add the appropriate flags, e.g.:
# gcc -std=c11 -Wall -Wextra -O2 -Iinclude -o frpg src/*.c -lncurses
```

## Run

After building, run the executable:

```bash
./frpg
```

If your executable or run steps are different, update this section accordingly.

## Project layout (common)

- src/        - C source files
- include/    - Header files
- assets/     - Game assets (images, maps, text files)
- build/      - Build artifacts (ignored in version control)
- tests/      - Unit or integration tests
- docs/       - Additional documentation

Adjust these to match the repository's actual layout.

## Contributing

Contributions are welcome. Suggested workflow:

1. Fork the repository.
2. Create a feature branch: `git checkout -b feature/your-feature`
3. Make changes and add tests where appropriate.
4. Commit and push: `git commit -am "Add feature" && git push origin feature/your-feature`
5. Open a pull request describing the change.

Please follow the project's style and add/update tests for new functionality.

## Testing

If tests are provided, run them with the project's test runner or:

```bash
# if there is a Makefile target
make test
```

Otherwise, run any unit test binaries in the tests/ directory.

## License

No license specified. To make this project open source, add a LICENSE file (for example, MIT, Apache-2.0, or GPL-3.0) and update this section.

## Contact

If you have questions or ideas, open an issue or contact the repository owner.
