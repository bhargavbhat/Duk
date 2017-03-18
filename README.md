## Duk
Duk is a simple terminal based application for assisting with [Rubber Duck Debugging](https://en.wikipedia.org/wiki/Rubber_duck_debugging). Rather than speak to an inanimate object, you can now chat with a simple program and try to reason about your code.

### Build
- Duk requires `readline` development libraries. On Ubuntu, this can be installed by running `install_deps.sh` script
- run `make` to compile the program, the executable is called `duk` (as in `duck` with a typo missing out `c`)

### Features
- Autocomplete : requires `tags` file to be present in the same directory as the executable (symlinks will work fine too)
- History : you can recall previously entered text with `UpArrow` and `DownArrow` keys

### Commands
- `exit` : Will exit the program, as will `quit`, `q` and `x`
- `help` : displays short help message

### Screenshot
![Duk Screenshot](duk.png?raw=true "Duk in Action")
