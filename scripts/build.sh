#!/bin/sh


INCLUDE_DIR=src

MAIN=src/main.c
FIELD=src/field/field.c
RENDER=src/render/render_terminal.c

OUTPUT=build/main


clang -I $INCLUDE_DIR  $MAIN $FIELD $RENDER  -o $OUTPUT
