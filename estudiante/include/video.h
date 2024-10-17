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

/**
 * @brief T.D.A. Video
 * 
 * Una instancia del tipo de dato abstracto Video nos permite almacenar una secuencia de imágenes.
 * 
 * El TDA Video proporciona distintas herramientas para la manipulación de dichas imágenes, como son la inserción 
 * y borrado de fotogramas, la lectura y escritura de videos en disco, el rebobinado de un video y la realización 
 * de morphing entre dos imagenes.
 * 
 * \include video.h
 * 
 * @authors Gabriel Josué Marcano Grimán
 *          Ángel Rodíguez Faya
 * 
 * @date Octubre 2024
 */
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

    /**
     * @brief Lee un video de un directorio.
     * Lee los frames de un video almacenados en el directorio especificado y los guarda en el vector imagenes.
     *
     * @param path Ruta del directorio donde se encuentran los frames del video.
     * @pre path debe ser un directorio valido y que contenga imagenes ".pgm".
     * @return true si la lectura del video ha tenido exito, false si no.
     */
    bool LeerVideo(const string & path);


    /**
     * @brief Escribe los frames del video en un directorio.
     * Toma los elementos del vector imagenes del video y los almacena en el directorio especificado.
     *
     * @param path Ruta del directorio donde se quiere guardar los frames.
     * @param prefijo Prefijo que tendran las imagenes que se guardaran.
     * @pre el video no puede estar vacio, es decir, size() > 0.
     * @return true si la escritura ha tenido exito, false si no.
     */
    bool EscribirVideo(const string & path, const string &prefijo)const;

    /**
     * @brief Rebobina un video.
     * Sobrescribe el contenido del video sobre el que se llama el metodo con los frames de v en orden inverso.
     *
     * @param v Video que se quiere rebobinar.
     * @pre v debe tener al menos 2 frames.
     * @return Video con los frames de v en orden inverso.
     */
    Video Rebobinar(const Video &v);

    /**
     * @brief Realiza el morphing entre dos imagenes.
     * Realiza una transicion entre dos imagenes, creando una ilusion de transformacion.
     * 
     * @param I1 Imagen inicial de la que se parte.
     * @param I2 Imagen final.
     * @param nf Numero de pasos para realizar la transformacion.
     * @pre I1 y I2 deben tener el mismo tamaño, es decir, el mismo numero de filas y columnas.
     * @pre nf > 0, el numero de pasos no puede ser 0.
     * @return Video con el morphing entre las dos imagenes.     
     */
    Video Morphing(const Image &I1, const Image &I2, int nf);

    /**
     * @brief Devuelve un iterador que apunta al principio del vector imagenes.
     * @return Iterador que apunta al primer elemento del vector imagenes.
     */
    vector<Image>::iterator begin();

    /**
     * @brief Devuelve un iterador constante que apunta al principio del vector imagenes.
     * @return Iterador constante que apunta al primer elemento del vector imagenes.
     */
    vector<Image>::const_iterator begin() const;

    /**
     * @brief Devuelve un iterador que apunta al elemento siguiente al ultimo del vector imagenes.
     * @return Iterador que apunta al elemento siguiente al ultimo del vector imagenes..
     */
    vector<Image>::iterator end();

    /**
     * @brief Devuelve un iterador constante que apunta al elemento siguiente al ultimo del vector imagenes.
     * @return Iterador constante que apunta al elemento siguiente al ultimo del vector imagenes..
     */
    vector<Image>::const_iterator end() const;

    /**
     * @brief Devuelve un iterador inverso constante que apunta al primer elemento del vector imagenes invertido.
     * @return Iterador inverso constante que apunta al primer elemento del vector imagenes invertido.
     */
    vector<Image>::const_reverse_iterator rbegin() const;

    /**
     * @brief Devuelve un iterador inverso constante que apunta al elemento siguiente al ultimo del vector imagenes invertido.
     * @return Iterador inverso constante que apunta al elemento siguiente al ultimo del vector imagenes invertido.
     */
    vector<Image>::const_reverse_iterator rend() const;
};

#endif // VIDEO__H
