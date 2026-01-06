
# Simple Random-Walk (SDL2)

A minimal, fast and clean implementation of **Random-Walk** in C.  
Rendering is done using **SDL2**, and the simulation demonstrates Agents walking in random ways.

---

## Features

- Customisable amount of Agents  
- Simple Random-Walk simulation
- Minimal and readable C code  

---

## Requirements

You need:

- a C compiler (e.g. `clang` or `gcc`)
- SDL2 development libraries  
  (on macOS via Homebrew: `brew install sdl2`)

---

## Build

Compile using:

```sh
gcc main.c -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2 -lm -o main
```

**Important:**  
You must link against:

- `-lSDL2` → SDL library  
- `-lm` → math library (for `sin`, `cos`, `pow`, etc.)

---

## Run

```sh
./main <number_of_agents> // if left empty, it goes to the default value 5
```

---

## Repository

Clone the project:

```sh
git clone https://github.com/Goldinyan/Random-Walk.git
```

---

## License

MIT License — see `LICENSE` file.

---
