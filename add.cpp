#include <string>
using namespace std;
#include <fstream>
#include <iostream>
#include "func.hpp"
#include <cmath>

using namespace std;
pool* MemPool(){
    pool *Mpool;
    Mpool=new pool;
    int block=sizeof(image::HEADER)+256*256*(sizeof(image::chanels))+sizeof(mem_block_info);//size of block
  //  int mem_block=sizeof(image::HEADER)+256*256*sizeof(image::chanels);
    Mpool->size=10*block; //for 10 images
    Mpool->begin=new char[Mpool->size];
    Mpool->end=Mpool->begin+Mpool->size;
    for (int i=0; i<Mpool->size; i++){
        Mpool->begin[i]=0;
    }
    cout<<"size:"<<Mpool->size<<endl;
    cout<<"begin:"<<reinterpret_cast<image*>(Mpool->begin)<<endl;
    cout<<"end:"<<reinterpret_cast<image*>(Mpool->end)<<endl;
    if (true){
        return Mpool;
        } 
    else{
        return nullptr;
    } 
}

IMG* new_pool(pool* Mpool, int size, image::HEADER header, image::chanels *mat){
    char* ptr=Mpool->begin;
    while((ptr+sizeof(mem_block_info)+size)<Mpool->end){
        if(reinterpret_cast<mem_block_info*>(ptr)->allocated==1)
        {
            int curr_block_size=reinterpret_cast<mem_block_info*>(ptr)->block_size;
            ptr=ptr+sizeof(mem_block_info)+curr_block_size;
        }
        else if(reinterpret_cast<mem_block_info*>(ptr)->allocated==0){
            reinterpret_cast<mem_block_info*>(ptr)->allocated=1;
            reinterpret_cast<mem_block_info*>(ptr)->block_size=size;
            cout<<"Memory successfully allocated"<<endl;
            cout<<"the point is:"<<reinterpret_cast<mem_block_info*>(ptr)->block_size<<endl;
            return (reinterpret_cast<IMG*>(ptr+sizeof(mem_block_info)));
        }
        else{
            cout<<"No memory allocated."<<endl;
            return (nullptr);
        }
    }
}
void create_tga(char* filename, image::HEADER header, image::chanels *mat){
    fstream file;

    cout<<"Start!"<<endl;
    file.open(filename, ios::out | ios::binary);
    if (!file)
    {
        cout << "Error in opening "<< endl;
    }
       cout<<"File is ready for the work."<<endl;
       

     file.write(reinterpret_cast<char*>(&header), sizeof(image::HEADER));
    
 for (int i=0;i<header.height*header.width;i++){
        file.write(reinterpret_cast<char*>(&mat->r), sizeof(char));
        file.write(reinterpret_cast<char*>(&mat->g), sizeof(char));
        file.write(reinterpret_cast<char*>(&mat->b), sizeof(char));
       }
    file.close();

}

void create_gradient(char* filename, image::HEADER header, image::chanels *mat){
    fstream file;
    cout<<"Start!"<<endl;
    file.open(filename, ios::out | ios::binary);
    if (!file)
    {
        cout << "Error in opening "<< endl;
    }
       cout<<"File is ready for the work."<<endl;
       file.write(reinterpret_cast<char*>(&header), sizeof(image::HEADER));
       for (int i=0;i<header.width;i++){
           for (int j=0; j<header.height; j++){
               int k=i+j;
               mat->g=k;
               mat->b=k;
               mat->r=k;
               file.write(reinterpret_cast<char*>(&mat->r), sizeof(char));
               file.write(reinterpret_cast<char*>(&mat->g), sizeof(char));
               file.write(reinterpret_cast<char*>(&mat->b), sizeof(char));
           }
       }
    file.close();
}

void ReadFile(char* filename, image::HEADER header, image::chanels *mat){
    fstream file;
    cout<<"Start!"<<endl;
    file.open(filename, ios::out | ios::binary);
    if (!file)
    {
        cout << "Error in opening "<< endl;
    }
    else {
        cout<<"Preparing for reading from file..."<<endl;
    }
    file.read(reinterpret_cast<char*>(&header), sizeof(image::HEADER));
    
    cout<<reinterpret_cast<int*>(&header.bitsperpixel)<<endl;
       for (int i=0;i<header.height*header.width;i++){
        file.read(reinterpret_cast<char*>(&mat->r), sizeof(char));
        file.read(reinterpret_cast<char*>(&mat->g), sizeof(char));
        file.read(reinterpret_cast<char*>(&mat->b), sizeof(char));
}
cout<<"Reading from file completed!"<<endl;
}

void OpenGile(char* filename);