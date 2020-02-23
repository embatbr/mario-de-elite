#!/bin/bash

export PROJECT_ROOT_PATH="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd ${PROJECT_ROOT_PATH}


EXEC_FILENAME="game.exe"


if test -f "${EXEC_FILENAME}"; then
    rm ${EXEC_FILENAME}
fi

gcc \
    -std=c99 \
    code/main.c code/logging.c \
    code/controllers/base.c code/controllers/logic.c \
    code/game/base.c code/game/building.c code/game/logic.c \
    code/graphics/base.c code/graphics/drawing.c \
    code/physics/base.c \
    -o ${EXEC_FILENAME} \
    $(pkg-config --libs allegro-5 allegro_image-5 allegro_primitives-5)

if test -f "${EXEC_FILENAME}"; then
    ./${EXEC_FILENAME}
fi