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

DIR="$1"
RED='\033[1;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color
#FILES="${DIR}/*.c"
FILES=$(find "$DIR" -type f -name "*.c")
gcc -Wall -Wextra -std=c11 -O2 -c src/gamma_test.c
gcc -Wall -Wextra -std=c11 -O2 -c src/gamma.c
gcc -Wall -Wextra -std=c11 -O2 -c src/safe_malloc.c
gcc -Wall -Wextra -std=c11 -O2 -c src/ufind.c
counter=0
for f in $FILES; do
  base=$(basename "${f}")
  name="${base::-2}"
  cp "${f}" ./src
  gcc -Wall -Wextra -std=c11 -O2 -c "src/${base}"
  gcc  -o gamma "${name}.o" gamma.o safe_malloc.o ufind.o
  #valgrind --error-exitcode=15 --leak-check=full --show-leak-kinds=all -q ./gamma
  ./gamma
  if [ $? -eq 0 ]; then
    echo -e "${GREEN} ${f} passed${NC}"
  else
    counter=$((counter+1))
    echo -e "${RED} ${f} didn't pass ${NC}"
  fi
  rm -f "${name}.o" "src/${base}"
done
ctrl_c
