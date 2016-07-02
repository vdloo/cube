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
    front        180° ↺        180° ↶
   +b-b-b---+    +b-b-b---+    +g-g-g---+ 
  / b b b  /|   / b b b  /|   / g g g  /| 
 /  b b b / |  /  b b b / |  /  g g g / | 
+--------+rrr +--------+ooo +--------+ooo 
|        |rrr |        |ooo |        |ooo 
|w  w  w |rrr |y  y  y |ooo |w  w  w |ooo 
|w  w  w | /  |y  y  y | /  |w  w  w | /  
|w  w  w |/   |y  y  y |/   |w  w  w |/   
+--------+    +--------+    +--------+    
cube is solved!
performing superflip
    front        180° ↺        180° ↶
   +b-y-b---+    +b-w-b---+    +g-y-g---+ 
  / o b r  /|   / r b o  /|   / r g o  /| 
 /  b w b / |  /  b y b / |  /  g w g / | 
+--------+rbr +--------+obo +--------+ogo 
|        |wry |        |yow |        |woy 
|w  b  w |rgr |y  b  y |ogo |w  g  w |obo 
|o  w  r | /  |r  y  o | /  |r  w  o | /  
|w  g  w |/   |y  g  y |/   |w  b  w |/   
+--------+    +--------+    +--------+    
cube is not solved :(
performing superflip
    front        180° ↺        180° ↶
   +b-b-b---+    +b-b-b---+    +g-g-g---+ 
  / b b b  /|   / b b b  /|   / g g g  /| 
 /  b b b / |  /  b b b / |  /  g g g / | 
+--------+rrr +--------+ooo +--------+ooo 
|        |rrr |        |ooo |        |ooo 
|w  w  w |rrr |y  y  y |ooo |w  w  w |ooo 
|w  w  w | /  |y  y  y | /  |w  w  w | /  
|w  w  w |/   |y  y  y |/   |w  w  w |/   
+--------+    +--------+    +--------+    
cube is solved!
```

# Installation
```
$ ./bootstrap && ./configure && make
```
