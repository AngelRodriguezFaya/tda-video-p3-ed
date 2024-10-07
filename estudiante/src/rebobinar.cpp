#include <cstdlib>
#include <iostream>
#include <string>

#include <video.h>

using namespace std;


int main (int argc, char ** argv) {

    Video origen, destino;

    if (argc != 5){
        cerr << endl << "Error: Número de parámetros incorrecto. " << endl;
        cerr << "Uso: " << argv[0] << " <RutaVideo> <Prefijo> <NumImages> <Dest>" << endl << endl;
        exit (1);
    }

    // TODO: Aplicar el codigo necesario para rebobinar el video origen y almacenar las imagenes en destino
    // para ello es necesario definir las funciones que leen y escriben un videdo como una secuencia de imagenes en una ruta dada
}


