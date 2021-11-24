#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// read the input from given filename and return a 2D dynamically allocated and populated array
// you can use char type for each cell value or bool from <stdbool.h>
int **read_from_file(const char *filename)
{
    FILE *x;
    int count;
    count = 0;
    int iterations;
    int rows;
    int columns;
    int i;
    int** currentiteration;
    i = -1;
    x = fopen(filename,"r");//opens the file
    if (x != NULL)
    {
        char line[1024];
        while(fgets(line, 1024, x) != NULL){//goes on reading every line until there is no line remaining in the text file
            if(count == 0){
               count++;
               iterations = atoi(line);
                //catches the first line and converts it into an int
            }
            else if(count == 1){
                count++;
                rows = atoi(line);
                 //catches the second line and converts it into an int
            }
            else if(count == 2){
                count++;
                columns = atoi(line);
                 //catches the third line and converts it into an int
                int k;
                currentiteration = (int**)malloc(rows * sizeof(int*));
                for (k = 0; k < rows; k++){
                    currentiteration[k] = (int*) malloc(columns * sizeof(int));
                } //mallocs enough space on the heap for each column inside the rows
            }
            else{
                i++;
                count++;
                int j;
                for( j = 0; j < columns; j++){
                    if(line[j] == '-'){//checks each character in the line and assigns either 1 or 0 to the corresponding location in the heap
                    //depending on the line's character either being - or X
                        currentiteration[i][j] = 0;
                    }
                    else{
                        currentiteration[i][j] = 1;
                    }
                }
            }
        }
    }
    return currentiteration;
    fclose(x);
}

// given a game step return the next step applying game rules
char **next_state(char **state)
{
   return NULL;
}

// bonus task
// return true if the given pattern is an oscillator
bool is_oscillator(char **pattern, int max_steps)
{
    return NULL;
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

int main(int argc, char *argv[]) 
{
   const char *input;
   input = argv[1];
   const char *output;
   output = argv[2];//gets the inputs of the input path and the output path
   //with open (input,"r") as f:
   read_from_file(input);
    return 0;
}               
