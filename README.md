cube
====

Rubik's cube implementation in C.

Building
```
git clone git@github.com:vdloo/cube.git
cd cube
make
```

Make your computer try to solve the cube:
```
make run
```

```
./cube
start cube looks like:
    +b-b-b---+     +b-b-b---+ 
   / b b b  /|    / b b b  /| 
  /  b b b / |   /  b b b / | 
 +--------+rrr  +--------+ooo 
 |        |rrr  |        |ooo 
 |w  w  w |rrr  |y  y  y |ooo 
 |w  w  w | /   |y  y  y | /  
 |w  w  w |/    |y  y  y |/   
 +--------+     +--------+    
cube is solved!

shuffling cube
    +o-r-b---+     +y-w-g---+ 
   / b w o  /|    / o w b  /| 
  /  g w y / |   /  b r o / | 
 +--------+bwo  +--------+wyy 
 |        |bbg  |        |ogb 
 |r  y  o |gro  |w  g  g |bob 
 |g  r  r | /   |g  o  r | /  
 |y  b  w |/    |r  y  w |/   
 +--------+     +--------+    
cube is not solved :(

starting bogosolve
tried 1000000 rotations
    +w-w-g---+     +y-b-r---+ 
   / g g w  /|    / w g g  /| 
  /  r b y / |   /  g w w / | 
 +--------+byg  +--------+wry 
 |        |byo  |        |yww 
 |b  o  w |roo  |r  b  b |gwg 
 |y  o  y | /   |o  r  r | /  
 |w  g  o |/    |o  r  b |/   
 +--------+     +--------+    
cube is not solved :(
```

# Installation
```
$ ./bootstrap && ./configure && make
```
