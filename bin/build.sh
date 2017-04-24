#!/bin/bash
clear
echo ""
echo ""
echo "---------- CMAKE ---------"
export CC=clang
export CXX=clang++
cmake -DCMAKE_CXX_FLAGS=-g  -DCMAKE_BUILD_TYPE=Debug ..

if [ $? -ne 0 ]; then
	echo "Failed to run Cmake"
	exit;
fi

echo ""
echo "---------- MAKE ---------"
make
	
if [ $? -ne 0 ]; then
	echo "Failed to run make"
	exit;
fi

if [[ $0 -eq "build" ]]; then
	echo "Done"
	exit;
fi

if [[ $0 -eq "debug" ]]; then
	echo ""
	echo "---------- RUN ---------"
	gdb ./src/game/GAME -x run
else
	./src/game/GAME
fi
