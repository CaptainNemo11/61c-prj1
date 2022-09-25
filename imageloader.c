/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	//YOUR CODE HERE
	FILE* ppm = fopen(filename,"r");
	Image* img=(Image*)malloc(sizeof(Image));
	char format[3];
	int size;
	Color* color;
	int scale;
	fscanf(ppm,"%s",format);
	if(strcmp(format,"P3") == 0){
		fscanf(ppm,"%d%d",&(img->cols),&(img->rows));
		fscanf(ppm,"%d",&scale);
		size=img->cols*img->rows;
		img->image=(Color**)malloc(sizeof(Color*)*size);
		for (size_t i=0; i<size; i++){
			color=(Color*)malloc(sizeof(Color));
			fscanf(ppm,"%hhu%hhu%hhu",&(color->R),&(color->G),&(color->B));
			img->image[i]=color;
		}
	fclose(ppm);
	return img;
	}else{
		fclose(ppm);
		return NULL;
	}
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	//YOUR CODE HERE
	printf("P3\n");
	printf("%d %d\n",image->cols,image->rows);
	printf("255\n");
	size_t num;
	for (size_t i=0; i<(image->rows); i++){
		num=image->cols *i;
		printf("%3d %3d %3d",image->image[num]->R,image->image[num]->G,image->image[num]->B);
		for(size_t j=1; j<(image->cols); j++){
			num=image->cols * i +j;
			printf("   %3d %3d %3d",image->image[num]->R,image->image[num]->G,image->image[num]->B);
		}
		printf("\n");
	}
	
}

//Frees an image
void freeImage(Image *image)
{
	//YOUR CODE HERE
	for (size_t i=0; i<(image->cols)*(image->rows); i++){
		free(image->image[i]);
	}
	free(image->image);
	free(image);
}