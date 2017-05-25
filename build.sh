#!/bin/bash
mkdir bin
cd bin
clear
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

if [[ $1 = "build" ]]; then
	echo "Done"
	exit;
fi

if [[ $1 = "debug" ]]; then
	echo ""
	echo "---------- DEBUG ---------"
	gdb ./src/game/GAME -x run
else
	echo ""
	echo "---------- RUN ---------"
	./src/game/GAME
fi
echo ""
