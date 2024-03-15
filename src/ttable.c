#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRING_LENGTH 1000
#define MAX_VARIABLES 26

//Function to format and print the truth table
void printTable(int variableNumber, const char *formula);
//Function to calculate the result boolean from an RPN formula
int calculateFormula(const char *formula, int *operands);

int main(int argc, char const *argv[])
{
    if(argc!=3){ //Checks to make sure there are 3 arguments including the name of the program
        fprintf(stderr,"Usage: ttable <variable_num> <formula>\n");
        return 1;
    }

    int variableNumber = atoi(argv[1]); //Converts string variable number to integer

    if ( variableNumber<1 || variableNumber>MAX_VARIABLES){ //Ensures a valid number of variables has been used
        fprintf(stderr,"Error: <variable_num> must be between 1 and 26\n");
        return 1;
    }

    const char *formula = argv[2]; //Stores formula argument in a constant char pointer

    if (strlen(formula)>MAX_STRING_LENGTH){ //Ensures a valid formula length has been used
        fprintf(stderr,"Error: <formula> exceeds max length of %d characters\n",MAX_STRING_LENGTH);
        return 1;
    }

    printTable(variableNumber, formula);

    return 0; //Return 0 upon successful run

}

void printTable(int variableNumber, const char *formula){
    int rows = 1 << variableNumber; //Bitwise left shift operation to effectively calculate 2^varNum
    int operands[variableNumber];

    for(int i=0; i<variableNumber;i++){
        printf("%c ",'a'+i); //Print appropriate letter variable in increasing order by adding i to 'a'
    }

    printf(": %s : Result\n",formula);

    for (long unsigned int i = 0; i < 2 * variableNumber + 11 + strlen(formula); i++) {
        printf("=");
    }
    printf("\n"); //printf statements to generate table in correct format

    for(int row=0; row<rows; row++){ //For loop iterates over every row in the table
        for (int var = variableNumber-1; var >=0; var--) {
            operands[var] = (row >> (variableNumber-1-var)) & 1; //Calculate values for each variable in the current row
        }

        for (int var = 0; var < variableNumber; var++) { //Print the values for the current row
            printf("%d ", operands[var]);
        }

        printf(" :   %d\n", calculateFormula(formula,operands)); //Calculate and print the result value

    }

}

int calculateFormula(const char *formula, int *operands){
    int stack[MAX_STRING_LENGTH]; //Array to implement stack for calculating formula truth values
    int top=-1;

    printf(": ");

    for(int i=0; formula[i]!='\0'; i++){ //For loop to iterate over each formula character
        if(islower(formula[i])){ //Checks if character is a lower case letter and adds variable to stack
            stack[++top]=operands[formula[i]-'a'];
            printf(" ");
        }
        else if(formula[i]=='0' || formula[i]=='1'){ //Checks if character is a 1 or 0 constant and adds it to stack
            stack[++top]= formula[i]-'0';
            printf(" ");
        }
        else{ //Else it checks if it is a symbol

            int operand2=stack[top--]; //Pops the operand from the stack
            int operand1; //Declares operand

            if(formula[i]!='-' && top>-1){ //Checks if negation symbol or if the formula starts with a symbol
                operand1=stack[top--];
            } else {operand1 = 0;} //Otherwise initialises operand 1 as to 0

            switch (formula[i]) //Switch with case for each symbol allowed
            {
            case '|':
                stack[++top]=operand1|operand2;
                break;
            case '&':
                stack[++top]=operand1&operand2;
                break;
            case '#':
                stack[++top]=operand1^operand2;
                break;
            case '>':
                stack[++top]=(!operand1)|operand2;
                break;
            case '=':
                stack[++top]=operand1==operand2;
                break;
            case '-':
                stack[++top]=!operand2; //Negation symbol works on one operand
                break;
            default:
                fprintf(stderr, "Error: formula not following RPN syntax\n"); //Default statement for all other symbols
                exit(EXIT_FAILURE);
                break;
            }
            printf("%d",stack[top]); //Prints the result of that operation
        }
    }
    if (top != 0) { //Ensures stack is empty in order to validate formula
        fprintf(stderr, "Error: formula not following RPN syntax\n");
        exit(EXIT_FAILURE); //Else exit with message
    }
    return stack[top]; //Return final result which would be stack top
}