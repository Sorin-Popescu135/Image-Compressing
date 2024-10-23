/*Popescu Sorin - 314CD*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structsandfunc.h"

int main(int argc, char const *argv[]) {
    FILE *file = fopen(argv[argc - 2], "rb");
    char bck;
    char task[3];
    strcpy(task, argv[1]);
    FILE *fileout;

    if(strstr(task, "-c1")) {
        fileout = fopen(argv[argc - 1], "w");
    } else if(strstr(task, "-c2")){
        fileout = fopen(argv[argc - 1], "wb");
    }
    
    int prag = atoi(argv[2]);
    int pos = 1;
    int nr = 0;
    int size_maxi = 0;
    char type[3];
    fscanf(file, "%s", type);
    type[2] = '\0';
    unsigned int width, height, max_col_value;

    // read info from file

    fscanf(file, "%d", &width);
    fscanf(file, "%d", &height);
    fscanf(file, "%d", &max_col_value);
    fscanf(file, "%c", &bck);
    Pixel **grid = (Pixel **) malloc(sizeof(Pixel *) * width);
    for(int i = 0; i < width; i++) {
        grid[i] = malloc(sizeof(Pixel) * height);
    }

    Tree root = CreateNode(1);

    // read the pixels and place them into a matrix

    Pixel tmppixel;
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++){
            fread(&tmppixel, sizeof(Pixel), 1, file);
            grid[i][j] = tmppixel;
        }
    }

    // call the function that divides the image and creates the quadtree

    breaking(grid, width, &size_maxi, 0, 0, prag, pos, &nr, NULL, root);

    // output for task 1

    int maxlev = getLevels(root);
    if(strstr(task, "-c1")){
        fprintf(fileout, "%d\n", maxlev);
        fprintf(fileout, "%d\n", nr);
        fprintf(fileout, "%d\n", size_maxi);
    }

    // output for task 2

    if(strstr(task, "-c2")){
        unsigned int size = height;
        fwrite(&size, sizeof(unsigned int), 1, fileout);
        for(int i = 1; i <= maxlev; i++){
            Get_Level_Nodes(root, i, fileout);
        } 
    }

    fclose(file);
    fclose(fileout);

    // free memory allocated for the matrix

    for(int i = 0; i < height; i++){
        free(grid[i]);
    }
    free(grid);
    FreeArbor(root);

    return 0;
}
