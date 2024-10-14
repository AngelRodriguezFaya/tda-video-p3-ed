/**
 * @file morphing.cpp
 * @brief Fichero que realiza el morphing entre dos imágenes.
 *
 * @authors Gabriel Josué Marcano Grimán
 *          Ángel Rodíguez Faya
 *
 * @date Octubre 2024
 *
 * Implementación de la funcion Morphing perteneciente al TDA Video.
 */
#include <cstdlib> 
#include <iostream> 

#include <image.h>
#include <video.h>

using namespace std; 


int main (int argc, char ** argv) {

  Image origen, destino;
  Video morphing, video;
  
  // Comprobamos que el número de parámetros sea correcto
  if (argc != 5){
    cerr << endl << "Error: Número de parámetros incorrecto. " << endl;
    cerr << "Uso: " << argv[0] << " <Imagen_1> <Imagen_2> <Directorio_de_salida> <nf>" << endl << endl;
    exit (1);
  }

  // Cargamos las imágenes origen y destino
  if (!origen.Load(argv[1])){
    cerr << "Error: " << argv[1] << " no es un fichero PGM válido" << endl;
    exit(1);
  }
  if (!destino.Load(argv[2])){
    cerr << "Error: " << argv[2] << " no es un fichero PGM válido" << endl;
    exit(1);
  }

  // Leemos el directorio donde se desea almacenar el video
  string path = argv[3];

  // Leemos el número de pasos para realizar el morphing.
  int nf = atoi(argv[4]);

  morphing = video.Morphing(origen, destino, nf);

  if(morphing.EscribirVideo(path, "morphing")){
    cout << "Escritura del video en disco realizada con éxito." << endl;
  }else{
    cerr << "Error al escribir el video en disco." << endl;
    exit(1);
  }

  return 0;
}


