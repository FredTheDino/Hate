#!/bin/bash
clear
echo ""
echo ""
echo "---------- CMAKE ---------"
cmake -DCMAKE_BUILD_TYPE=Debug ..

if [ $? -ne 0 ]; then
	exit;
fi

echo ""
echo "---------- MAKE ---------"
make
	
if [ $? -ne 0 ]; then
	exit;
fi

echo ""
echo "---------- RUN ---------"
gdb ./src/game/GAME -x run
