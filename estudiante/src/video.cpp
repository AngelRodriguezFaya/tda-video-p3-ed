/**
 * @file video.cpp
 * @brief Fichero con definiciones para los métodos de la clase Video.
 *
 * @authors Gabriel Josué Marcano Grimán
 *          Ángel Rodíguez Faya
 *
 * @date Octubre 2024
 *
 * Implementación del TDA Video.
 */

#include <cstring>
#include <cassert>
#include <iostream>

#include <image.h>
#include "video.h"
#include <filesystem> // Para leer el path
#include <algorithm>  // Para sort.

namespace fs = std::filesystem;

/********************************
        Constructores
*********************************/

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

/***************************************************
   Funciones atómicas de la clase Video.
****************************************************/

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


/***************************************************
    Metodos de los Iteradores de la clase Video.
****************************************************/
vector<Image>::iterator Video::begin(){
    return(imagenes.begin());
}

vector<Image>::const_iterator Video::begin() const{
    return(imagenes.begin());
}

vector<Image>::iterator Video::end(){
    return(imagenes.end());
}

vector<Image>::const_iterator Video::end() const{
    return(imagenes.end());
}

vector<Image>::const_reverse_iterator Video::rbegin() const{
    return(imagenes.rbegin());
}

vector<Image>::const_reverse_iterator Video::rend() const{
    return(imagenes.rend());
}

/***************************************************
    Metodos de la clase Video.
****************************************************/

bool Video::LeerVideo(const string & path){

    fs::path ruta = path;  // Ruta del directorio donde se encuentran las imágenes.

    vector<string> nombresImagenes;  // Vector auxiliar para almacenar las imágenes.

    // Verificamos que el path sea un directorio.
    if (fs::exists(ruta) && fs::is_directory(ruta)){        
       
        // Iteramos sobre los archivos del directorio.
        for (const auto &it : fs::directory_iterator(ruta)){
            
            // Verificamos que el archivo sea una imagen PGM.
            if (it.path().extension() == ".pgm"){
                Image img;
                bool resultado = img.Load(it.path().c_str());   // c_str() hace una conversión para devolver un puntero a char.
                
                // Si se ha podido leer la imagen, la añadimos al vector de imagenes.
                if (resultado)
                    nombresImagenes.push_back(it.path().filename());
                
                // Si nos se ha podido leer la imagen, mostramos un mensaje de error.
                else{
                    cout << "Error al leer la imagen: " << it.path().filename() << endl;
                    cout << "Se finaliza la lectura del video." << endl;
                    return false;
                }
            }
        }
    }

    // Si el path no es un directorio, finalizamos la lectura del video.
    else{
        cout << "Error: " << path << " no es un directorio valido para leer el video." << endl;
        cout << "Se finaliza la lectura del video." << endl;
        return false;
    }

    // Ahora que hemos leido todas las imágenes, las ordenamos y las añadimos al vector imagenes
    
    // Ordenamos las imágenes en el vector auxiliar.
    sort(nombresImagenes.begin(), nombresImagenes.end());
    cout << "---Imagenes ordenadas.---" << endl;
    
    for(int i = 0; i < nombresImagenes.size(); i++){
        Image img;
        
        bool resultado = img.Load((path + nombresImagenes[i]).c_str());
        if (resultado){     
            this->insertar(i, img);   // Llamo a la función insertar de la clase Video para añadir la imagen al video.
        }
    }

    cout << "---Imagenes añadidas al video.---" << endl;

    // Llegados a este punto, la lectura del video se ha realizado con éxito.
    cout << "El video se ha leido con éxito." << endl;
    return true;  
}

bool Video::EscribirVideo(const string & path, const string &prefijo)const{

    fs::path ruta = path;

    // Compruebo que el video no esta vacio.
    if(this->size() > 0){

        //Compruebo que el path existe y es un directorio.
        if(fs::exists(ruta) && fs::is_directory(ruta)){

            for(int i = 0; i < imagenes.size(); i++){
                Image img = (*this)[i];
                string path_completo = path + prefijo + to_string(i) + ".pgm";
                
                if(!img.Save(path_completo.c_str())){
                    cout << "Imagen: " << prefijo + to_string(i) + ".pgm" << " no ha podido ser escrita" << endl;
                    cout << "Se cancela la escritura del video." << endl;
                    return false;
                }
            }
        } 
        
        else{
            cout << "Error: " << path << " no es un directorio valido para escribir el video." << endl;
            cout << "Se finaliza la escritura del video." << endl;
            return false;
        }
    } 
    
    else{
        cout << "El video esta vacio, no tiene fotogramas." << endl;
        cout << "Se finaliza la escritura del video." << endl;
        return false;
    }

    cout << "La escritura del video en el disco se ha realizado con exito" << endl;
    return true;
}

Video Video::Rebobinar(const Video &v){

    // Comprobamos que el video de origen v no esta vacio.
    assert(v.size() > 1);

    imagenes.clear();               // Borramos las imagenes de este video (*this).
    imagenes.reserve(v.size());     // Reservamos tanto espacio en este video como imagenes tiene el video de origen.
    int i = 0;

    for (vector<Image>::const_reverse_iterator rit = v.rbegin(); rit != v.rend(); ++rit){
        insertar(i, *rit);
        i++;
    }
    
    return *this; // Devolvemos el video con las imagenes en orden inverso.
}

Video Video::Morphing(const Image &I1, const Image &I2, int nf){

    //Comprobamos que se han introducido correctamente los parámetros.
    assert( (I1.get_rows() == I2.get_rows()) && (I1.get_cols() == I2.get_cols()));
    assert(nf > 0);

    cout << "Los parametros introducidos son correctos." << endl;
    cout << "Se procede a realizar el morphing. Espere un momento..." << endl;

    //Preparamos este video (el que llama al metodo) que contendra las imagenes del morphing.
    imagenes.clear();           // Borramos las imagenes de este video.
    imagenes.reserve(nf);       // Reservamos espacio para nf imagenes.

    for (double i = 0; i < nf; i++){  // Indice i de la imagen en la que nos encontramos.

        // Creo la imagen que ira en la posicion i del vector.
        Image img(I1.get_rows(), I1.get_cols(), 0); 

        for(int k = 0; k < img.get_rows(); k++){
            for(int f = 0; f < img.get_cols(); f++){

                double v1 = static_cast<double>(I1.get_pixel(k, f));
                double v2 = static_cast<double>(I2.get_pixel(k, f));

                double valor = (v1 * (1-(i/nf))) + ((v2*i)/nf);      // Formula para hacer morphing.

                pixel valor_pixel = static_cast<pixel>(valor);
                    
                img.set_pixel(k, f, valor_pixel);
            }
        }

            // Añado la imagen al video.
            this->insertar(i, img);    
    }

    cout << "El morphing se ha realizado correctamente." << endl;
    return *this;
}


