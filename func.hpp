#ifndef FUNC_HPP
#define FUNC_HPP
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>

class image
{
public:
#pragma pack(push, 1)
    class HEADER
    {
    public:
        //HEADER();
        char idlength;
        char colourmaptype;
        char datatypecode;
        short int colourmaporigin;
        short int colourmaplength;
        char colourmapdepth;
        short int x_origin;
        short int y_origin;
        short width;
        short height;
        char bitsperpixel;
        char imagedescriptor;
    };
#pragma pack(pop)

    struct chanels {
        unsigned int r;
        unsigned int g;
        unsigned int b;
    };
    union COL {
        unsigned int color;
        chanels matrix;
    };
};



class IMG{
    image::HEADER head;
    image::chanels chan;

};



struct pool
{
    int size;
    char *begin;
    char *end;
};

struct mem_block_info
{
    int allocated;
    int block_size;
};

pool* MemPool();

IMG* new_pool(pool* Mpool, int size, image::HEADER header, image::chanels *mat);
void create_tga(char *filename, image::HEADER header, image::chanels *mat);
void ReadFile(char *filename, image::HEADER header, image::chanels *mat);
void OpenGile(char *filename);
#endif