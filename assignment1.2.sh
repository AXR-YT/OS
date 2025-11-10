#!/bin/bash

echo "Simple Calculator"
echo "Enter first number:"
read num1

echo "Enter an operator (+, -, *, /):"
read op

echo "Enter second number:"
read num2

case $op in
  +)
    result=$((num1 + num2))
    ;;
  -)
    result=$((num1 - num2))
    ;;
  '*')
    result=$((num1 * num2))
    ;;
  /)
    if [ $num2 -eq 0 ]; then
      echo "Error: Division by zero is not allowed."
      exit 1
    else
      # For division that results in decimal, use bc
      result=$(echo "scale=2; $num1 / $num2" | bc)  #scale=2 for 2 decimals, bc=basic calculator
    fi
    ;;
  *)
    echo "Invalid operator"
    exit 1
    ;;
esac

echo "Result: $result"