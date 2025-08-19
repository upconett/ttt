#!/bin/sh


INCLUDE_DIR=src

MAIN=src/main.c
FIELD=src/field/field.c
GAME=src/game/game.c
UI=src/ui/ui_terminal.c

OUTPUT=build/main


clang -I $INCLUDE_DIR  $MAIN $FIELD $RENDER $GAME $UI -lncurses  -o $OUTPUT
