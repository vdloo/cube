AM_CFLAGS = -Wall -Wextra -O2 -mtune=native -fcommon
bin_PROGRAMS = cube
SHARED_CFILES = mechanics.c rotations.c representation.c operations.c status.c patterns.c solver.c
SHARED_HFILES = mechanics.h rotations.h representation.h operations.h status.h patterns.h solver.h
CUBE_CFILES = cube.c
CUBE_HFILES = cube.h
cube_SOURCES = $(CUBE_CFILES) $(CUBE_HFILES) $(SHARED_CFILES) $(SHARED_HFILES)
