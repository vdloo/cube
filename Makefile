.PHONY: all run clean

NAME := cube
VERSION := 0.1
MAINTAINER := Rick van de Loo <rickvandeloo@gmail.com>, Ruud van Asseldonk <dev@veniogames.com>
DESCRIPTION := Cube in C

all:
	gcc cube.c -o cube
run:
	./cube
clean:
	git clean -xfd

