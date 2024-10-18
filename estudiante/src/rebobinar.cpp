/**
 * @file rebobinar.cpp
 * @brief Fichero que rebobina un video.
 *
 * @authors Gabriel Josué Marcano Grimán
 *          Ángel Rodíguez Faya
 *
 * @date Octubre 2024
 *
 * Implementación de la funcion Rebobinar perteneciente al TDA Video.
 *
 * Ejemplo de uso:
 * ~$ cmake CMakeLists.txt
 * ~$ make
 * ~$ ./rebobinar estudiante/datos/imagenes/f1_panas estudiante/datos/rebobinado
 */

#include <cstdlib>
#include <iostream>
#include <string>

#include <video.h>

using namespace std;

int main (int argc, char ** argv) {

    Video origen, destino;

    if (argc != 3){
        cerr << endl << "Error: Número de parámetros incorrecto. " << endl;
        cerr << "Uso: " << argv[0] << " <DirectorioEntrada> <DirectorioSalida>" << endl << endl;
        exit (1);
    }

    origen.LeerVideo(argv[1]);

    destino.Rebobinar(origen);

    destino.EscribirVideo(argv[2], "rebobinar");
}



