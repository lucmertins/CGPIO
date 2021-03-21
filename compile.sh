#!/bin/sh
echo "compilando\n"

gcc src/main.c -o gpiotest -lgpiod

echo "executando\n\n"

./gpiotest