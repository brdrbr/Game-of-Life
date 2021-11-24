#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int iterations;
int rows;
int columns;
int** currentiteration;
char** outputmatrix;
const char *output;
int livecount;
int deadcount;

// print the game state
// after each step you can call this function, add some delay and then clear screen to create a simple game simulation in terminal
void print_state(int **state)
{
    int i, j;
    printf("\nNext State:\n");
    for(i=0; i<rows; i++){
        for(j=0; j<columns; j++){
            printf("%d", state[i][j]);
        }
        printf("\n");
    }
}

// print the game state
// after each step you can call this function, add some delay and then clear screen to create a simple game simulation in terminal
void print_statechar(char **state)
{
    int i, j;
    printf("\nNext State:\n");
    for(i=0; i<rows; i++){
        for(j=0; j<columns; j++){
            printf("%c", state[i][j]);
        }
        printf("\n");
    }
}

// read the input from given filename and return a 2D dynamically allocated and populated array
// you can use char type for each cell value or bool from <stdbool.h>
void read_from_file(const char *filename)
{
    FILE *x;
    int count;
    count = 0;
    int i;
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
                        //printf("%d", currentiteration[i][j]);
                    }
                    else{
                        currentiteration[i][j] = 1;
                        //printf("%d", currentiteration[i][j]);
                    }
                }
            }
        }
    }
    //print_state(currentiteration);
    fclose(x);
}

// given a game step return the next step applying game rules
void next_state()
{

    int** nextstate;
    int k;
    nextstate = (int**)malloc(rows * sizeof(int*));
    for (k = 0; k < rows; k++){
        nextstate[k] = (int*) malloc(columns * sizeof(int));
    }//sets up the nextstate in the heap
    int i;
    int j;

    int** aliveneighbors;
    int l;
    aliveneighbors = (int**)malloc(rows * sizeof(int*));
    for (l = 0; l < rows; l++){
        aliveneighbors[l] = (int*) malloc(columns * sizeof(int));
    }//we need another matrix to fill before we fill the nextstate matrix, this matrix will hold the number of alive neighbors for each cell
    for (i = 0; i < rows; i++){
        for (j = 0; j < columns; j++){
            aliveneighbors[i][j] = 0;//initializes the aliveneighbors since we will increment its values inside the 2d array
        }
    } 

    //char matrix for converting int cells to actual char outputs
    outputmatrix = (char**)malloc(rows * sizeof(char*));
    for (l = 0; l < rows; l++){
        outputmatrix[l] = (char*) malloc(columns * sizeof(char));
    }

    for (i = 0; i < rows; i++){//these for statements allow us to fill the alive neighbors matrix
       for (j = 0; j < columns; j++){
           if( i > 0 && j > 0){ //makes sure top left neighbor exists
               aliveneighbors[i][j] = aliveneighbors[i][j] + currentiteration[i-1][j-1];
           }
           if( i>0 && j< columns - 1){//makes sure top right neighbor exists
               aliveneighbors[i][j] += currentiteration[i-1][j+1];
           }
           if( i>0){//makes sure top neighbor exists
               aliveneighbors[i][j] += currentiteration[i-1][j];
           }
           if( i< rows - 1 && j>0){ //makes sure bottom left neighbor exists
               aliveneighbors[i][j] += currentiteration[i+1][j-1];
           }
           if( i < rows-1 && j< columns - 1){//makes sure bottom right neighbor exists
               aliveneighbors[i][j] += currentiteration[i+1][j+1];
           }
           if( i < rows - 1){//makes sure bottom neighbor exists
               aliveneighbors[i][j] += currentiteration[i+1][j];
           }
           if(j>0){//makes sure left neighbor exists
               aliveneighbors[i][j] += currentiteration[i][j-1];
           }
           if(j < columns - 1){//makes sure right neighbor exists
               aliveneighbors[i][j] += currentiteration[i][j+1];
           }
        }
    } 
    int r;
    int f;
    deadcount = 0;
    livecount = 0;
    for (r = 0; r < rows; r++){//these for statements allow us to fill the next iteration matrix
       for (f = 0; f < columns; f++){
           if(currentiteration[r][f] == 0){
               if(aliveneighbors[r][f] == 3){
                   nextstate[r][f] = 1;//if the number of neighbors is 3, it will come alive
                   livecount++;
               }
               else{
                   nextstate[r][f] = 0;//else it will stay dead
               }
           }
           else{
               if(aliveneighbors[r][f] == 2  || aliveneighbors[r][f] == 3){
                   nextstate[r][f] = 1;//if the number of neighbors is 2 or 3 it will stay alive
               }
               else{
                   nextstate[r][f] = 0;//else it will die
                   deadcount++;
               }
           }
       }
    }    
    for (r = 0; r < rows; r++){//these for statements allow us to transform the currentiteration matrix to our actual current iteration from the previous iteration 
                                //by using the nextstate as a type of "dummy state"
       for (f = 0; f < columns; f++){
           currentiteration[r][f] = nextstate[r][f];
       }
    }    
    for (i = 0; i < rows; i++){
        for (j = 0; j < columns; j++){
            if(currentiteration[i][j] == 0){
                outputmatrix[i][j] = '-';
            }
            else{
                outputmatrix[i][j] = 'X';
            }
        }
    } 
    //print_state(currentiteration);
    //printf("%d\n", deadcount);
    //printf("%d\n", livecount);
    //print_statechar(outputmatrix);

}

// bonus task
// return true if the given pattern is an oscillator
bool is_oscillator(char **pattern, int max_steps)
{
    return NULL;
}

int main(int argc, char *argv[]) 
{
   const char *input;
   input = argv[1];
   output = argv[2];//gets the inputs of the input path and the output path
   read_from_file(input);
   int w;
   for(w = 0; w < iterations; w++){
       next_state();
       char slive[12];
       char sdead[12];
       sprintf(slive,"%d", livecount);
       sprintf(sdead,"%d", deadcount);
       FILE *y;
        y = fopen(output,"w");
   }
   return 0;
}               
