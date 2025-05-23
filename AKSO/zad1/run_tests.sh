#!/bin/bash

# Kolory terminala
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Lista testów
tests=("one" "two" "connections" "undetermined" "delete" "params" "malicious" "pipeline" "shift" "cycle" "alloc" "memory" "weak" "disconnect")


# Flaga do śledzenia błędów
all_passed=true

echo "=== Running Moore Automaton Tests ==="

for test in "${tests[@]}"; do
  echo -n "Test '$test'... "
  ./example "$test" > /dev/null
  result=$?
  if [ $result -eq 0 ]; then
    echo -e "${GREEN}OK${NC}"
  elif [ $result -eq 1 ]; then
    echo -e "${RED}FAILED${NC}"
    all_passed=false
  elif [ $result -eq 2 ]; then
    echo -e "${YELLOW}UNKNOWN TEST NAME${NC}"
    all_passed=false
  else
    echo -e "${RED}UNKNOWN ERROR (exit code $result)${NC}"
    all_passed=false
  fi
done

echo "====================================="

if $all_passed; then
  echo -e "${GREEN}All tests passed.${NC}"
  exit 0
else
  echo -e "${RED}Some tests failed.${NC}"
  exit 1
fi