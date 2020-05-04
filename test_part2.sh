#!/bin/bash
trap ctrl_c INT
function ctrl_c() {
  rm "$EXEC".out "$EXEC".err
  rm vgcore.* 2> /dev/null
  #rm -rf test_build

  printf "\n\n--\n number of tests that didn't pass: "
  if [ "$err_counter" -eq 0 ]; then
    echo -e "${GREEN}0"
  else
    echo -e "${RED} $err_counter"
  fi
  exit 0
}

function progress_bar {
    let _progress=(${1}*100/${2}*100)/100
    let _done=(${_progress}*4)/10
    let _left=40-$_done
    _fill=$(printf "%${_done}s")
    _empty=$(printf "%${_left}s")
printf "\r[${_fill// /#}${_empty// /-}] ${_progress}%%"
}


if [ ! -d "test_build" ] ; then
    # shellcheck disable=SC2164
    mkdir test_build && cd test_build
    cmake ..
    cd ..
fi
cd test_build && make >/dev/null && cd ..

EXEC="gamma_test"
PROG="test_build/gamma"
REAL_PROG="$(realpath "$PROG")"
DIR="$1"

RED='\033[1;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

err_counter=0
progress_count=0
progress_max="$(find ${DIR}/*.in | wc -l)"

progress_bar ${progress_count} ${progress_max}
FILES="${DIR}/*.in"
for f in $FILES; do

  progress_count=$((progress_count+1))
  out="${f::-2}"
  out="${out}out"
  err="${f::-2}"
  err="${err}err"

  valgrind --error-exitcode=15 --leak-check=full --show-leak-kinds=all -q "$REAL_PROG" <"$f" >"$EXEC".out 2>"$EXEC".err

  # Reset progress bar
  printf "\r                                                \r"

  DIFF1="$(diff "$out" "$EXEC".out)"
  DIFF2="$(diff "$err" "$EXEC".err)"
  if [ "$DIFF1" ] || [ "$DIFF2" ]; then
    err_counter=$((err_counter+1))
    echo -e "${RED} ${f} didn't pass ${NC}"
  else
    echo -e "${GREEN} ${f} passed${NC}"
  fi

  progress_bar ${progress_count} ${progress_max}
done
ctrl_c
