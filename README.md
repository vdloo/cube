[![Build Status](https://travis-ci.org/vdloo/cube.svg?branch=master)](https://travis-ci.org/vdloo/cube)

cube
====

Rubik's cube solver in C.

Make your computer try to solve the cube:
```
$ time ./src/cube
start cube looks like:
    front         180° ↺         180° ↶
   +b-b-b---+     +b-b-b---+     +g-g-g---+ 
  / b b b  /|    / b b b  /|    / g g g  /| 
 /  b b b / |   /  b b b / |   /  g g g / | 
+--------+rrr  +--------+ooo  +--------+ooo 
|        |rrr  |        |ooo  |        |ooo 
|w  w  w |rrr  |y  y  y |ooo  |w  w  w |ooo 
|w  w  w | /   |y  y  y | /   |w  w  w | /  
|w  w  w |/    |y  y  y |/    |w  w  w |/   
+--------+     +--------+     +--------+    
cube is solved!

performing DLFUR'MEL'
    front         180° ↺         180° ↶
   +y-r-r---+     +y-o-o---+     +w-w-w---+ 
  / y y y  /|    / y y y  /|    / w w w  /| 
 /  o o y / |   /  r r y / |   /  r r g / | 
+--------+grw  +--------+bgg  +--------+ygb 
|        |obb  |        |bgo  |        |ogb 
|w  y  r |ybb  |g  g  o |bgy  |b  b  o |ggb 
|w  o  g | /   |y  r  o | /   |g  o  w | /  
|o  b  b |/    |r  r  o |/    |r  y  w |/   
+--------+     +--------+     +--------+    
cube is not solved :(

Finding a solution
checking 2 levels deep
checking 3 levels deep
checking 4 levels deep
checking 5 levels deep
checking 6 levels deep
checking 7 levels deep
checking 8 levels deep
Found a solution!
    front         180° ↺         180° ↶
   +b-b-b---+     +b-b-b---+     +g-g-g---+ 
  / b b b  /|    / b b b  /|    / g g g  /| 
 /  b b b / |   /  b b b / |   /  g g g / | 
+--------+rrr  +--------+ooo  +--------+ooo 
|        |rrr  |        |ooo  |        |ooo 
|w  w  w |rrr  |y  y  y |ooo  |w  w  w |ooo 
|w  w  w | /   |y  y  y | /   |w  w  w | /  
|w  w  w |/    |y  y  y |/    |w  w  w |/   
+--------+     +--------+     +--------+    
cube is solved!
Found a solution, path is: LE'M'RU'F'L'D'

real	5m43.150s
```

# Building
```
$ git clone git@github.com:vdloo/cube.git
$ ./bootstrap && ./configure && make
```

# Installation
```
# make install
```
