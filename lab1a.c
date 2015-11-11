/*
 * lab1a.c
 *
 *  Created on:
 *      Author:
 */

/* include helper functions for game */
#include "lifegame.h"
#include  <stdio.h>
#include  <string.h>
#include  <unistd.h>




/* add whatever other includes here */
#define X_VAL 10
#define Y_VAL 10

char board[Y_VAL][X_VAL];
char temp_board[Y_VAL][X_VAL];
int state;
char filename[] = "init_file.txt";
char glider[] = "glider.txt";
char worldfile[] = "world.txt";

/* number of generations to evolve the world */
#define NUM_GENERATIONS 50

/* functions to implement */
void init_board(void);
void search_neighbors(int x, int y);
int set_on_state(int x, int y, int neighbors);


/* this function should set the state of all
   the cells in the next generation and call
   finalize_evolution() to update the current
   state of the world to the next generation */
void next_generation(void);
/* this function should return the state of the cell
   at (x,y) in the next generation, according to the
   rules of Conway's Game of Life (see handout) */
int get_next_state(int x, int y);

/* this function should calculate the number of alive
   neighbors of the cell at (x,y) */
int num_neighbors(int x, int y);

int main(void)
{
	//int n;
	
	char myfile[256];

	fputs("Please enter a file name to read from : \n", stdout);
	fgets(myfile, 256, stdin);
	printf("file = %s\n", myfile);


	if( access(myfile, F_OK) != -1)
		initialize_world_from_file(myfile);
	else
	{
		initialize_world_from_file(glider);
		printf("cant find file : %s initialising world from default file \n", myfile);
	}


	output_world();


	save_world_to_file(worldfile);

	/* TODO: initialize the world */
	//init_board();
	/*initialize_world();
	output_world();
        printf(" num neigh %d \n", num_neighbors(1,2));

	for (n = 0; n < NUM_GENERATIONS; n++)
	{
		next_generation();
		if(n == 1)
			output_world();
	}*/

	/* TODO: output final world state */
	//output_world();
	return 0;
}


void init_board(void)
{
	memset(board, ' ', sizeof(board[0][0]) * Y_VAL * X_VAL);
	memset(temp_board, ' ' , sizeof(temp_board[0][0]) * Y_VAL * X_VAL);
}

void next_generation(void) {
	/* TODO: for every cell, set the state in the next
	   generation according to the Game of Life rules

	   Hint: use get_next_state(x,y) */

	int x, y;

	for(y = 0; y < get_world_height(); y++)
	{

		for(x = 0; x < get_world_width(); x++)
		{
			set_cell_state(y,x,get_next_state(x,y));
		}

	}
        
	finalize_evolution(); /* called at end to finalize */
}

int get_next_state(int x, int y) {
	/* TODO: for the specified cell, compute the state in
	   the next generation using the rules

	   Use num_neighbors(x,y) to compute the number of live
	   neighbors */

	   /* rows referred to as x and columns y. this is not very intuative!!
  		e.g. x-axis.y-axis*/ 

           int no_neighbors,curr_state;
           
           if(get_cell_state(y,x) == 1)
	   {
		curr_state = 1;
	   }
	   else
	   {
		curr_state = 0;
	   }

	   no_neighbors = num_neighbors(x,y);


	   if(curr_state == 0  &&  no_neighbors == 3)
	   {
		//cell becomes alive!!
		return ALIVE;
	   }
	   else if(curr_state == 1)
	   {
		return	set_on_state(x,y, no_neighbors);
	   }
        
 	   return DEAD;
}


int set_on_state(int x, int y, int no_neighbors)
{

	if(no_neighbors < 2  || no_neighbors > 3)
	{
		return DEAD;
	}
	else if(no_neighbors == 2 || no_neighbors == 3)
	{
           	return ALIVE;
	}

	return DEAD;
}



int num_neighbors(int x, int y) {

	   /*Use get_cell_state(x,y) no, not right now!! as not 
           not implemented */
	int count = 0; 
  	int y_start, x_start, x_end,y_end;

	if(x == 0)
	    x_start = 0;
	else
	    x_start = x -1;

	if(x == X_VAL - 1)
	    x_end = x;
	else
	    x_end = x +1;

	if(y == 0)
            y_start = 0;
	else
	    y_start = y -1;

	if(y == Y_VAL - 1)
	    y_end = y;
	else
            y_end = y + 1;


	int yind;
        int xind;
	

		for(yind = y_start; yind < y_end + 1;  yind++)
		{
			for(xind = x_start; xind < x_end + 1; xind++)
			{
				if(xind == x  &&  yind == y)
				{
					continue;
				}

				if(get_cell_state(yind,xind) == ALIVE)
				{
					count++;
				}
			 }

		}


	return count;
            
}

void search_neighbors(int x, int y)
{

	int y_start, x_start, x_end,y_end;

	if(x == 0)
	    x_start = 0;
	else
	    x_start = x -1;

	if(x == X_VAL - 1)
	    x_end = x;
	else
	    x_end = x +1;

	if(y == 0)
            y_start = 0;
	else
	    y_start = y -1;

	if(y == Y_VAL - 1 )
	    y_end = y;
	else
            y_end = y + 1;


	printf("start_x = %d, start_y = %d, end_x = %d, end_y  = %d \n", x_start, y_start, x_end, y_end);

}
