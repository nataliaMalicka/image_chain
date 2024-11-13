#include "block.h"
#include <cmath>
#include <iostream>

int Block::width() const
{
    //Returns the number of columns (width of 2d array), ret 0 if no col
return data.size();
}
int Block::height() const
{
    // Returns the length of column (height of 2d array), ret 0 if empty image
    if (data.size() == 0) {
        return 0;
    } else {
        return data[0].size();
    }
}

void Block::render(PNG &im, int column, int row) const
{
for (int x = 0; x < width(); x++) {
    for (int y = 0; y < height(); y++) {
        RGBAPixel pix = data[x][y];
        *im.getPixel(x + column,y + row) = pix;
    }
} 
}

void Block::build(PNG &im, int column, int row, int width, int height)
{
int maxHeight = (im.height()) - row;
int maxWidth = (im.width()) - column;
width = min(width, maxWidth);
height = min(height, maxHeight);


data = vector<vector<RGBAPixel>>(width, vector<RGBAPixel>(height));
for (int x=0; x < width; x++) {
    for (int y=0; y < height; y++) {
        RGBAPixel* pix = im.getPixel(x+column,y+row);
        data[x][y] = *pix;
    }
}
}

void Block::flipHoriz()
{
vector<vector<RGBAPixel>> destBlock(width(), vector<RGBAPixel>(height()));
for (int x=0; x < width(); x++) {
    for (int y=0; y < height(); y++) {
        destBlock[width() - x - 1][y] = data[x][y];
    }
}
data = destBlock;
}

void Block::flipVert()
{
vector<vector<RGBAPixel>> destBlock(width(), vector<RGBAPixel>(height()));
for (int x=0; x < width(); x++) {
    for (int y=0; y < height(); y++) {
        destBlock[x][height() - y - 1] = data[x][y];
    }
}
data = destBlock;
}

void Block::rotateRight()
{
//width set to dest img height and vice versa
vector<vector<RGBAPixel>> destBlock(height(), vector<RGBAPixel>(width()));
for (int x=0; x < width(); x++) {
    for (int y=0; y < width(); y++) {
        destBlock[height()- y - 1][x] = data[x][y];
    }
}
    data = destBlock;
}
