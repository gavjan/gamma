#!/bin/bash

trap ctrl_c INT
function ctrl_c() {
  rm -f gamma *.o vgcore.*
  rm -f src/"${base}"
  printf "\n\n--\n number of tests that didn't pass: "
  if [ "$err_counter" -eq 0 ]; then
    echo -e "${GREEN}0"
  else
    echo -e "${RED} $err_counter"
  fi
  exit 0
}
function compile() {
  gcc -std=c11 -Wall -Wextra -O3 -DNDEBUG -c src/gamma.c
  gcc -std=c11 -Wall -Wextra -O3 -DNDEBUG -c src/safe_malloc.c
  gcc -std=c11 -Wall -Wextra -O3 -DNDEBUG -c src/ufind.c
  gcc -std=c11 -Wall -Wextra -O3 -DNDEBUG -c src/list.c
}
function progress_bar {
    let _progress=(${1}*100/${2}*100)/100
    let _done=(${_progress}*4)/10
    let _left=40-$_done
    _fill=$(printf "%${_done}s")
    _empty=$(printf "%${_left}s")
    printf "\r[${_fill// /#}${_empty// /-}] ${_progress}%%"
}

DIR="$1"
RED='\033[1;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color
#FILES="${DIR}/*.c"
FILES=$(find "$DIR" -type f -name "*.c")
err_counter=0

progress_count=0
progress_max="$(find "$DIR" -type f -name "*.c" | wc -l)"

for f in $FILES; do

  progress_count=$((progress_count+1))
  base=$(basename "${f}")
  name="${base::-2}"
  cp "${f}" ./src
  gcc -std=c11 -Wall -Wextra -O3 -DNDEBUG  -c "src/${base}"
  if [ ! -f "gamma.o" ] || [ ! -f "safe_malloc.o" ] || [ ! -f "ufind.o" ] || [ ! -f "list.o" ] ; then
    compile
  fi
  gcc  -o "$name" "${name}.o" gamma.o safe_malloc.o ufind.o list.o

  valgrind --error-exitcode=15 --leak-check=full --show-leak-kinds=all -q ./"$name"
  #./"$name"

  # Reset progress bar
  printf "\r                                                \r"

  if [ $? -eq 0 ]; then
    echo -e "${GREEN} ${f} passed${NC}"
  else
    err_counter=$((err_counter+1))
    echo -e "${RED} ${f} didn't pass ${NC}"
  fi
  rm "$name"
  rm -f "${name}.o" "src/${base}"

  progress_bar ${progress_count} ${progress_max}
done
ctrl_c
