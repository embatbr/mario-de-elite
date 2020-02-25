#!/bin/bash

export PROJECT_ROOT_PATH="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd ${PROJECT_ROOT_PATH}


EXEC_FILENAME="mario-de-elite.client"


if test -f "${EXEC_FILENAME}"; then
    rm ${EXEC_FILENAME}
fi

g++ \
    src/client/main.cpp \
    src/client/controllers/Keyboard.cpp \
    src/server/base/Point2D.cpp \
    -o ${EXEC_FILENAME} \
    $(pkg-config --libs allegro-5 allegro_image-5 allegro_primitives-5)

if test -f "${EXEC_FILENAME}"; then
    ./${EXEC_FILENAME}
fi