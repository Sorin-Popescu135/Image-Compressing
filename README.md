# Quadtree Image Compression

This project implements a **quadtree** structure in C to compress and partition images based on pixel color similarity. The quadtree recursively subdivides the image into smaller regions, stopping when the color variation within a region falls below a user-specified threshold. Large areas of uniform color are stored efficiently using this method, making it useful for image compression.

## Project Structure

- **main.c**: Contains the core logic for reading the image, building the quadtree, and writing the results.
- **structsandfunc.h**: Header file with the definitions of the structures (`Pixel`, `TreeNode`) and function prototypes.

## How It Works

1. The program reads an image file and divides it into square blocks of pixels.
2. It calculates the average color for each block and determines the color variation within that block.
3. If the variation is below a user-defined threshold, the block is stored as a single node in the quadtree.
4. If the variation is above the threshold, the block is subdivided into four smaller blocks, and the process continues recursively.
5. The result is a quadtree where each node represents a block of pixels, either as a uniform color or subdivided further.

## Key Features

- **Efficient Image Representation**: Large areas of uniform color are stored as single nodes, reducing memory usage.
- **Quadtree Structure**: Each node has four children representing the top-left, top-right, bottom-left, and bottom-right quadrants of the image.
- **Custom Threshold**: The user can control the compression level by adjusting the color variation threshold.

## Functions Overview

- **CreateNode**: Allocates memory and initializes a new quadtree node.
- **getLevels**: Calculates the depth of the quadtree.
- **mean_calculator**: Computes the mean squared difference of RGB values within a block.
- **breaking**: Recursively subdivides blocks based on color variation and constructs the quadtree.
- **Get_Level_Nodes**: Extracts nodes at a specific level of the quadtree for output.
- **FreeArbor**: Frees memory allocated for the entire quadtree structure.

## License
This project is open-source and available for modification and distribution.
