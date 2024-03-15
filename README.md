# Truth Table Generator

This program generates a truth table for a given logical formula in Reverse Polish Notation (RPN).

## Installation

No installation required. Simply compile the program using a C compiler such as GCC:

gcc -o ttable ttable.c

## Usage
Run the compiled program with two command-line arguments:

variable_num: Number of variables in the logical formula (integer between 1 and 26).

formula: Logical formula in RPN notation (e.g., "ab&c|").

./ttable < variable_num > < formula >

Example:

./ttable 3 ab&c|

## Program Structure
printTable(int variableNumber, const char *formula): Formats and prints the truth table.

calculateFormula(const char *formula, int *operands): Calculates the result boolean from an RPN formula.

## Limitations
The maximum length of the formula is limited to 1000 characters.

The maximum number of variables is limited to 26.

Created by Cristian Soare
