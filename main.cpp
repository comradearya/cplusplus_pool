#include <bitset>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <sstream>
#include <cmath>
#include <cstring>


#include "func.hpp"
using namespace std;

int main(int argc, char* argv[]){
    pool *Mpool;
    Mpool=MemPool(); //max memory
    IMG *img1;
    img1=nullptr;
    int mem_block=sizeof(image::HEADER)+256*256*sizeof(image::chanels);// for 1 image

   
    image::HEADER img;
    img.idlength=0;
    img.colourmapdepth=0;
    img.datatypecode=2;
    img.colourmaporigin=0;
    img.colourmaplength=0;
    img.colourmapdepth=24;
    img.x_origin=0;
    img.y_origin=0;
    img.width=256;
    img.height=256;
    img.bitsperpixel=24;
    img.imagedescriptor=0;
    
    image::chanels *mat;
         mat=new image::chanels[256*256*3];
   if (mat==nullptr){
           cout<<"ERR: No space for matrix."<<endl;
    }
    else if (mat!=nullptr){
        cout<<"Space for matrix is allocated!"<<endl;
    }
    
    if (argc<2){
        cout<<"PLease enter an argument."<<endl;}
for (int i=1;i<argc;i++){

    const char *cwhite="create_white";
if (!strcmp(argv[i],cwhite)){

        mat->r=255;
        mat->g=255;
        mat->b=255;
  
    char white[]="white.tga";
     img1=new_pool(Mpool, mem_block, img, mat);

    create_tga(white,img, mat);
    ReadFile(white, img, mat);
}
else if(strcmp(argv[i],"create_black")==0){

        mat->r=0;
        mat->g=0;
        mat->b=0;
  
    char black[]="black.tga";
    create_tga(black,img, mat);
}
else if(!(strcmp(argv[i],"create_color")))
{

mat->r=0;
mat->g=0;
mat->b=0;
    char gradient []="gradient.tga";
    create_tga(gradient, img, mat);
}

else {
    cout<<"Wrong command! Try again."<<endl;
}
    
    return 0;
}
delete []mat;
cout<<"Dynamical Memory cleaned"<<endl;

}
