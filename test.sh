#!/bin/bash

trap ctrl_c INT
function ctrl_c() {
  rm -f gamma *.o vgcore.*
  rm -f src/"${base}"
  printf "\n\n--\n number of tests that didn't pass: "
  if [ "$counter" -eq 0 ]; then
    echo -e "${GREEN}0"
  else
    echo -e "${RED} $counter"
  fi
  exit 0
}
function compile() {
  gcc -Wall -Wextra -std=c11 -O2 -c src/gamma.c
  gcc -Wall -Wextra -std=c11 -O2 -c src/safe_malloc.c
  gcc -Wall -Wextra -std=c11 -O2 -c src/ufind.c
}
DIR="$1"
RED='\033[1;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color
#FILES="${DIR}/*.c"
FILES=$(find "$DIR" -type f -name "*.c")
counter=0
for f in $FILES; do
  base=$(basename "${f}")
  name="${base::-2}"
  cp "${f}" ./src
  gcc -Wall -Wextra -std=c11 -O2 -c "src/${base}"
  if [ ! -f "gamma.o" ] || [ ! -f "safe_malloc.o" ] || [ ! -f "ufind.o" ] ; then
    compile
  fi
  gcc  -o "$name" "${name}.o" gamma.o safe_malloc.o ufind.o
  valgrind --error-exitcode=15 --leak-check=full --show-leak-kinds=all -q ./"$name"
  #./"$name"
  if [ $? -eq 0 ]; then
    echo -e "${GREEN} ${f} passed${NC}"
  else
    counter=$((counter+1))
    echo -e "${RED} ${f} didn't pass ${NC}"
  fi
  rm "$name"
  rm -f "${name}.o" "src/${base}"
done
ctrl_c
