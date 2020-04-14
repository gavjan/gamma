#!/bin/bash

PROG="gamma"
DIR="$1"
RED='\033[1;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color
#FILES="${DIR}/*.c"
FILES=$(find $directory -type f -name "*.in")
make gamma

for f in $FILES; do
  base="$(basename ${f})"
  name="${base::-2}"
  echo $name
  cp ${f} ./src
  gcc -Wall -Wextra -std=c11 -O2 -c "src/${base}"
  gcc  -o gamma "${name}.o" gamma.o safe_malloc.o ufind.o
  valgrind --error-exitcode=15 --leak-check=full --show-leak-kinds=all -q ./gamma -g
  if [ $? -eq 0 ]; then
    echo -e "${GREEN} ${name} passed${NC}"
  else
    echo -e "${RED} ${name} didn't pass ${NC}"
  fi
  rm -f "${name}.o" "src/${base}"
done
rm gamma *.o vgcore.*
