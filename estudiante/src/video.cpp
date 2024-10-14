#include <cstring>
#include <cassert>
#include <iostream>

#include <image.h>
#include "video.h"
#include <filesystem> // Para leer el path

namespace fs = std::filesystem;

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

    fs::path p = path;  // Ruta del directorio donde se encuentran las imágenes.

    // Verificamos que el path sea un directorio.
    if (fs::exists(p) && fs::is_directory(p)){        
       
        // Iteramos sobre los archivos del directorio.
        for (const auto &it : fs::directory_iterator(p)){
            
            // Verificamos que el archivo sea una imagen PGM.
            string extension = it.path().extension();
            if (extension == ".pgm"){
                Image img;
                bool resultado = img.Load(it.path().c_str());
                
                // Si se ha podido leer la imagen, la añadimos al video.
                if (resultado){     
                    imagenes.push_back(img);
                    cout << "Imagen leida: " << it.path().filename() << endl;
                }
                
                // Si nos e ha podido leer la imagen, mostramos un mensaje de error.
                else{
                    cout << "Error al leer la imagen: " << it.path().filename() << endl;
                    cout << "Se finaliza la lectura del video." << endl;
                    return false;
                }
            }
        }
    }

    // Si el path no es un dircetorio, finalizamos la lectura del video.
    else{
        cout << "Error: " << path << " no es un directorio válido." << endl;
        cout << "Se finaliza la lectura del video." << endl;
        return false;
    }

    // Llegados a este punto, la lectura del video se ha realizado con éxito.
    cout << "El video se ha leido con éxito." << endl;
    return true;  
}

bool Video::EscribirVideo(const string & path, const string &prefijo)const{
}

Video Video::Rebobinar(const Video &v){
}

Video Video::Morphing(const Image &I1, const Image &I2, int nf){

    //Comprobamos que se han introducido correctamente los parámetros.
    assert( (I1.get_rows() == I2.get_rows()) && (I1.get_cols() == I2.get_cols()));
    assert(nf > 0);

    cout << "Todo ok" << endl;

    //Creamos un video con nf fotogramas.
    Video morphing(nf);

    vector<Image>::iterator it = morphing.imagenes.begin();

    for (; it != morphing.imagenes.end(); it++){

        // Calculo el indice i de la imagen en la que nos encontramos.
        int i = it - morphing.imagenes.begin();

        // Si estamos en la primera imagen, la primera imagen del video será I1.
        if(it == morphing.imagenes.begin()){
            morphing.insertar(i, I1);
            cout << "primera imagen ok" << endl;
        }
        
        // Si estamos en la última imagen, la última imagen del video será I2.
        else if(it == morphing.imagenes.end() - 1){
            morphing.insertar(i, I2);
            cout << "ultima imagen ok" << endl;
        }

        // Entonces estamos en una imagen del centro.
        else{

            // Creo la imagen que ira en la posicion i del vector.
            Image img(I1.get_rows(), I1.get_cols(), 0); 
            // Voy iterando sobre los píxeles de la imagen.
            // No puedo hacerlo de otra forma que no sea la de utilizar un for de la forma mas basica,
            // ya que no puedo calcular por el numero de pixel por el que voy al igual que he hecho mas
            // arriba con el indice 'i', ya que la clase Iterator de la clase Image no trae implementado el
            // operador '-' para poder calcular la distancia entre el iterador y el principio de la imagen.

            for(int k = 0; k < (img.get_rows() * img.get_cols()); k++){

                int v_i1 = static_cast<int>(I1.get_pixel(k));
                int v_i2 = static_cast<int>(I2.get_pixel(k));

                int valor_pixel = v_i1 * ((1-i)/nf) + (v_i2*i)/nf;

                img.set_pixel(k, valor_pixel);
            }

            // Añado la imagen al video.
            morphing.insertar(i, img);
            cout << i << " imagen ok" << endl;

            // Actualizo el iterador del video
            ++it;   
        }     
    }

    cout << "morphing ok" << endl;
    return morphing;
}