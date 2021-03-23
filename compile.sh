#!/bin/sh
echo "compilando\n"

#gcc src/main.c -o gpiotest -lgpiod
./dockcross-linux-armv7a bash -c '$CC src/main.c -o gpiotest -lgpiod'

#echo "executando\n\n"
#./gpiotest