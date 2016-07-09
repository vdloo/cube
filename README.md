[![Build Status](https://travis-ci.org/vdloo/cube.svg?branch=master)](https://travis-ci.org/vdloo/cube)

cube
====

Rubik's cube solver in C.

Make your computer try to solve the cube:
```
$ # 5.5 second world record scramble
$ time ./src/cube "DDU'RRUFFDDU'RRU'B'LLR'B'DDUBBL'D'RR"
...

Cube pre-solved state: 
    front         180° ↺         180° ↶
   +g-g-r---+     +o-r-o---+     +w-y-b---+ 
  / o b b  /|    / b b o  /|    / r g y  /| 
 /  o r o / |   /  r g g / |   /  y b y / | 
+--------+wwb  +--------+wgy  +--------+ggr 
|        |oro  |        |yor  |        |roy 
|g  g  g |oyo  |w  w  r |rgg  |b  r  r |ygw 
|w  w  w | /   |b  y  b | /   |w  w  w | /  
|r  r  b |/    |b  o  y |/    |g  g  g |/   
+--------+     +--------+     +--------+    
Solved cube with 53 moves: MR'D'RFFR'ULLFMU'L'ULUFU'F'M'R'URZURU'L'UR'U'LFRUR'U'F'Z'RU'R'L'ULFRUR'U'F'URU'R'U'F'UFR'RUR'URUUR'UFRUR'U'F'REURU'R'U'F'UFFRUR'U'F'U'L'ULUFU'F'E'UU'L'ULUFU'F'FRUR'U'F'FRUR'U'F'URUR'URUUR'UUURUR'URUUR'UFRUR'U'F'FRUR'U'F'FRUR'U'F'URU'L'UR'U'LF'URU'L'UR'U'LFX

real    0m7.327s
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
