#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// read the input from given filename and return a 2D dynamically allocated and populated array
// you can use char type for each cell value or bool from <stdbool.h>
char **read_from_file(const char *filename)
{
    
}

// given a game step return the next step applying game rules
char **next_state(char **state)
{
   
}

// bonus task
// return true if the given pattern is an oscillator
bool is_oscillator(char **pattern, int max_steps)
{

}

// print the game state
// after each step you can call this function, add some delay and then clear screen to create a simple game simulation in terminal
void print_state(char **state, int rows, int cols)
{

    int i, j;
    printf("\nNext State:\n");
    for(i=0; i<rows; i++){
        for(j=0; j<cols; j++){
            printf("%c", state[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char **argv) 
{
   
    return 0;
}               
