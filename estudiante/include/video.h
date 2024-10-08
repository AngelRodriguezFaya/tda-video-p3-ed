/**
 * @file video.h
 * @brief Fichero de cabecera para la clase Video.
 *
 * @authors Gabriel Josué Marcano Grimán
 *          Ángel Rodíguez Faya
 *
 * @date Octubre 2024
 *
 * Implementación del TDA Video.
 */

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

    /**
    * @brief Constructor por defecto.
    * @post Genera una instancia de la clase Video con un vector instanciado a la clase Image
    * y que se encontrara con tamanio=0 y capacidad=1.
    * @return Video, el objeto video creado.    *
    */
    Video();

    /**
    * @brief Constructor de copia.
    * @param J Referencia al objeto Video que se desea copiar.
    * @return Video, el objeto video creado.
    */
    Video (const Video & J);

    /**
    * @brief Constructor con parámetros.
    * Crea un video en memoria con posibilidad para albergar n imagenes.
    * Reserva memoria para alojar el video.
    * @param n Número de imágenes que se desean almacenar en el video.
    * @pre n imagenes > 0
    * @post El video creado tiene n imagenes o casillas.
    *       El video creado contiene valores basura (no esta inicializado).
    * @return Video, el objeto video creado.
    */
    Video(int n);

    /**
    * @brief Destructor de la clase Video.
    * Libera la memoria reservada para el video.
    * @post El video destruido no puede volver a ser utilizado, salvo que se vuelva a
    *       realizar sobre él otra operación de construcción.
    */
    ~Video();

    /**
    * @brief Consultar el numero de imagenes/fotogramas del video.
    * @return El numero de fotogramas del video.
    */
    int size() const;

    /**
    * @brief Operador de asignación. Consultar/asignar una imagen al video.
    * @pre 0 <= n < size()
    * @return una referencia a la imagen asociada al fotograma foto-ésimo del video.
    */
    Image& operator[](int foto);

    /**
     * @brief Operador de asignación constante. Consultar una imagen del video.
     * @pre 0 <= n < size()
     * @return una referencia constante a la imagen asociada al fotograma foto-ésimo del video.
     */
    const Image& operator[](int foto) const;

    /**
    * @brief Insertar un nuevo fotograma/imagen en el video.
    * @param k Posicion en la que se desea insertar la imagen.
    * @param i Imagen que se desea insertar en el video.
    * @pre k debe indicar una posicion valida en el video, 0<=k<=V.size()
    * @return void
    * @post el video tiene un fotograma mas.
    */
    void insertar(int k, const Image& i);

    /**
    * @brief Borrar un fotograma/imagen del video.
    * @param k Posicion en la que se encuentra el fotograma que se desea borrar.
    * @pre k debe indicar una posicion valida en el video, 0<=k<V.size()
    * @return void
    * @post El video tiene un fotograma menos.
    */
    void borrar(int k);

    bool LeerVideo(const string & path);

    bool EscribirVideo(const string & path, const string &prefijo)const;


    };
};

#endif // VIDEO__H
