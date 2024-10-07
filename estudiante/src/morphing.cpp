#include <cstdlib> 
#include <iostream> 

#include <image.h>
#include <video.h>

using namespace std; 


int main (int argc, char ** argv) {

  Image origen, destino;
  Video morphing;
  
  if (argc != 4){
    cerr << endl << "Error: Número de parámetros incorrecto. " << endl;
    cerr << "Uso: " << argv[0] << " <fich_E> <fich_S> prefijo" << endl << endl;
    exit (1);
  }

  if (!origen.Load(argv[1])){
    cerr << "Error: " << argv[1] << " no es un fichero PGM válido" << endl;
    exit(1);
  }
  
  if (!destino.Load(argv[2])){
    cerr << "Error: " << argv[2] << " no es un fichero PGM válido" << endl;
    exit(1);
  }
  
  morphing.Morphing(origen, destino);
}


