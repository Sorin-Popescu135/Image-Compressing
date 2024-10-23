/*Popescu Sorin - 314CD*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// structures

typedef struct Pixel {
    unsigned char r;
    unsigned char g;
    unsigned char b;
}Pixel;


typedef struct TreeNode {
    Pixel *color;
    unsigned char type;
    int level;
    struct TreeNode *parent;
    struct TreeNode *topleft;
    struct TreeNode *topright;
    struct TreeNode *bottomright;
    struct TreeNode *bottomleft;
}TreeNode, *Tree;

// function for node creation

TreeNode *CreateNode(int pos) {
    TreeNode *node = (TreeNode *) malloc(sizeof(TreeNode));
    node->color = (Pixel *) malloc(sizeof(Pixel));
    node->color->r = 0;
    node->color->g = 0;
    node->color->b = 0;
    node->level = pos;
    node->parent = NULL;
    node->topleft = NULL;
    node->topright = NULL;
    node->bottomright = NULL;
    node->bottomleft = NULL;
    return node;
}


int maxi(int a, int b){
    if(a > b){
        return a;
    } else {
        return b;
    }
}

int getLevels(Tree root){
    if(root == NULL){
        return 0;
    }
    int max_level = root->level;

    max_level = maxi(max_level, getLevels(root->topleft));
    max_level = maxi(max_level, getLevels(root->topright));
    max_level = maxi(max_level, getLevels(root->bottomleft));
    max_level = maxi(max_level, getLevels(root->bottomright));

    return max_level;
}

unsigned long long mean_calculator(Pixel **grid, int size, int a, int b, unsigned long long red, unsigned long long green, unsigned long long blue) {
    unsigned long long mean = 0;

    for(int i = a; i < a + size; i++) {
        for(int j = b; j < b + size; j++) {
            mean = mean + (red - grid[i][j].r) * (red - grid[i][j].r);
            mean = mean + (green - grid[i][j].g) * (green - grid[i][j].g);
            mean = mean + (blue - grid[i][j].b) * (blue - grid[i][j].b);
        }
    }

    mean = mean / (3 * size * size);
    return mean;
}

void breaking(Pixel **grid,int size,int *size_maxi, int a, int b, int prag, int pos, int *nr, TreeNode *parent, TreeNode *current) {
    unsigned long long red = 0, green = 0, blue = 0;
    for(int i = a; i < a + size; i++) {
        for(int j = b; j < b + size; j++) {
            red = red + grid[i][j].r;
            green = green + grid[i][j].g;
            blue = blue + grid[i][j].b;

        }
    }
    red = red / (size * size);
    blue = blue / (size * size);
    green = green / (size * size);

    unsigned long long mean = mean_calculator(grid, size, a, b, red, green, blue);

    if(mean <= prag){
        current->color->r = red;
        current->color->g = green;
        current->color->b = blue;
        current->parent = parent;
        current->type = 1;
        current->level = pos;
        (*nr)++;
        if(size > *size_maxi) {
            *size_maxi = size;
        }
    } else {
        current->type = 0;
        size = size / 2;
        Tree rt = CreateNode(pos + 1);
        Tree lt = CreateNode(pos + 1);
        Tree rb = CreateNode(pos + 1);
        Tree lb = CreateNode(pos + 1);
        current->bottomleft = lb;
        lb->parent = current;
        current->bottomright = rb;
        rb->parent = current;
        current->topright = rt;
        rt->parent = current;
        current->topleft = lt;
        lt->parent = current;
        breaking(grid,size, size_maxi, a, b, prag, pos + 1, nr, current, lt);
        breaking(grid,size, size_maxi, a, b + size, prag, pos + 1, nr, current, rt);
        breaking(grid,size, size_maxi, a + size, b + size, prag, pos + 1, nr, current, rb);
        breaking(grid,size, size_maxi, a + size, b, prag, pos + 1, nr, current, lb);
    }
}


 void Get_Level_Nodes(TreeNode *root, int level, FILE *filecom){
    if(root->level == level){
        if(root->type == 0) {
           fwrite(&(root->type), sizeof(unsigned char), 1, filecom);
        } else if(root->type == 1) {
            fwrite(&(root->type), sizeof(unsigned char), 1, filecom);
            fwrite(&(root->color->r), sizeof(unsigned char), 1, filecom);
            fwrite(&(root->color->g), sizeof(unsigned char), 1, filecom);
            fwrite(&(root->color->b), sizeof(unsigned char), 1, filecom); 
        }
    } else if(root->level < level) {
        if(root->topleft != NULL){
            Get_Level_Nodes(root->topleft, level, filecom);
        }
        if(root->topright != NULL){
           Get_Level_Nodes(root->topright, level, filecom);
        }
        if(root->bottomright != NULL){
           Get_Level_Nodes(root->bottomright, level, filecom);
        }
        if(root->bottomleft != NULL){
            Get_Level_Nodes(root->bottomleft, level, filecom);
        }

    }
} 

void FreeArbor(TreeNode *root){
    if(root == NULL){
        return;
    }

    free(root->color);

    FreeArbor(root->topleft);
    FreeArbor(root->topright);
    FreeArbor(root->bottomright);
    FreeArbor(root->bottomleft);

    free(root);
}