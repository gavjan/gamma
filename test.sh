#!/bin/bash
EXEC="test_exec"
PROG="gamma"
REAL_PROG="$(realpath "$PROG")"
DIR="$2"
RED='\033[1;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color
FILES="${DIR}/*.in"
for f in $FILES; do
  out="${f::-2}"
  out="${out}out"

  err="${f::-2}"
  err="${err}err"
  valgrind --error-exitcode=15 --leak-check=full --show-leak-kinds=all -q "$REAL_PROG" -g <"$f" >"$EXEC".out 2>"$EXEC".err

  DIFF1="$(diff "$out" "$EXEC".out)"
  DIFF2="$(diff "$err" "$EXEC".err)"
  if [ "$DIFF1" ] || [ "$DIFF2" ]; then
    echo -e "${RED} ${f} didn't pass ${NC}"
  else
    echo -e "${GREEN} ${f} passed${NC}"
  fi
done
rm "$EXEC".out
rm "$EXEC".err
