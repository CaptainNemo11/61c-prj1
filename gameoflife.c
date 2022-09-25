/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	//YOUR CODE HERE
	uint32_t rows=image->rows;
	uint32_t cols=image->cols;
    Color* color = (Color*)malloc(sizeof(Color));
	Color* neigh[8]={NULL};
	int alive=0;
	int life,newlife;
	int newrow,newcol;
	uint8_t newR,newG,newB;
	if (color != NULL){
		for (int i=0; i<8; i++){
			for (newrow=row-1; newrow<=row+1; newrow++){
				for(newcol=col-1; newcol<=col+1; newcol++){
					if (newrow != row && newcol != col){
			            neigh[i]=image->image
							[cols*(newrow <0 ? rows-1:(newrow > rows-1? 0:newrow ))
								+(newcol <0 ? cols-1:(newcol >cols-1? 0: newcol))];
						if((int)(neigh[i]->R)+(int)(neigh[i]->G)+(int)(neigh[i]->B)){
							alive++;
						}else{
							neigh[i]=NULL;
						}
					}
				}
			}
		}
	life=(int)(image->image[cols*row+col]->R)+(int)(image->image[cols*row+col]->G)+(int)(image->image[cols*row+col]->B) 
			?1:0;
	newlife=(rule>>(alive+(life? 9:0)))&1U;
	if(newlife){
		newR=image->image[cols*row+col]->R;
        newG=image->image[cols*row+col]->G;
		newB=image->image[cols*row+col]->B;

		for(int i=0; i<8; i++){
			if(neigh[i] != NULL)	{
				newR += neigh[i ]->R;
				newG += neigh[i ]->G;
				newB += neigh[i ]->B;
			}
		}
		color->R=newR/alive;
		color->G=newG/alive;
		color->B=newB/alive;
	}else{
		color->R=color->G=color->B=0;
	}
	return color;
	}else{exit(-1);}
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
{
	//YOUR CODE HERE
	Image *new = (Image *)malloc(sizeof(Image));
	new->cols = image->cols;
	new->rows = image->rows;
	int rows=image->rows;
	int cols=image->cols;
	Color** newcolor=(Color**)malloc(sizeof(Color*)*rows*cols);
	for (int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
		newcolor[cols*i+j]=evaluateOneCell(image,i,j,rule);
		}
	}
	new->image=newcolor;
	freeImage(image);
	return new;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	if (argc != 3){
		printf("    usage: ./gameOfLife filename rule\n    filename is an ASCII PPM file (type P3) with maximum value 255.\n    rule is a hex number beginning with 0x; Life is 0x1808.\n");
		exit(-1);
	}
	char* endptr;
	Image* image=readData(argv[1]);
	image=life(image,strtol(argv[2],&endptr,16));
	writeData(image);
	freeImage(image);
	return 0;
}
