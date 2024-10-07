#ifndef VIDEO__H
#define VIDEO__H

#include <cstdlib>
#include <vector>
#include "image.h"

using namespace std;

class Video{

    private:

    vector<Image> imagenes;

    public:

    Video();

    Video (const Video & J);

    Video(int n);

    ~Video();

    int size() const;

    Image& operator[](int foto);

    const Image& operator[](int foto) const;

    void insertar(int k, const Image& i);

    void borrar(int k);

    bool LeerVideo(const string & path);

    bool EscribirVideo(const string & path, const string &prefijo)const;

    Video Rebobinar (const Video &v);

};

#endif // VIDEO__H
