#!/bin/bash
echo "---------- CMAKE ---------"
cmake ..
echo "---------- MAKE ---------"
make
echo "---------- RUN ---------"
./src/game/GAME
