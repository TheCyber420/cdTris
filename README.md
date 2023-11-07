# cdTris
Tetris clone using c + raylib for visuals and input

## Compiling and execution

Install Raylib from https://www.raylib.com/

```bash
  cd src
  make all
  ../bin/cdTris
```

# The goal
This project was done in order to get a basic graps of the Raylib library and to practice my c-code. 
It was coded with readability and expandability in mind. 
I chose tetris as it is not only fun to play, but also a good way to practice building a proper architecture for a program.  

## Chosen Ruleset
Tetris has many different rules depending on what version you play, for this clone I have chosen:

- Harddrop enabled
- 22 vertical tiles
- rotation in each direction
- standard piece rotation and offsets

## Default Controls

- Left:       a
- Right       d
- Soft Drop   s
- Hard Drop   Space Bar
- Rotate 90   w
- Rotate 180  q
- Rotate 270  e
- Hold piece  c
