#include <cstring>
#include <cassert>
#include <iostream>

#include <image.h>
#include "video.h"

Video::Video(){

    imagenes.reserve(1);

}

Video::Video (const Video & J) {

    imagenes.reserve(J.size());

    for (int i = 0; i < imagenes.size(); i++){
        imagenes[i] = J[i];
    }
}

Video::Video(int n){

    imagenes.reserve(n);

}

Video::~Video(){

    imagenes.clear();

}

int Video::size() const{

    return imagenes.size();

}

Image& Video::operator[](int foto){

    return imagenes[foto];

}

const Image& Video::operator[](int foto) const{

    return imagenes[foto];

}

void Video::insertar(int k, const Image& i){

    vector<Image>::iterator it = imagenes.begin() + k;
    imagenes.insert(it, i);

}

void Video::borrar(int k){

    vector<Image>::iterator it = imagenes.begin() + k;
    imagenes.erase(it);

}

bool Video::LeerVideo(const string & path){

    ifstream f(path);

    if (archivo){

    }

}