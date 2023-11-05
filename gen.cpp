#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 6) {
        cerr << "Uso: " << argv[0] << " <nombreArchivo> <longitudDeseada> <patronAInsertar> <repeticiones> <sector>" << endl;
        return 1;
    }


    string nombreArchivo = argv[1];
    int longitudDeseada = atoi(argv[2]);
    string patronAInsertar = argv[3];
    int repeticiones = atoi(argv[4]);
    int sector = atoi(argv[5]);

    ofstream archivo(nombreArchivo);

    if (!archivo) {
        cerr << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    srand(static_cast<unsigned>(time(0)));

    int caracteresEscritos = 0;
    int sectorInicio = 0;
    int sectorFin = 0;

    while (caracteresEscritos < longitudDeseada) {
        int longitudLinea = rand() % 101 + 100; // Entre 100 y 200 caracteres
        if (longitudDeseada - caracteresEscritos < 100) {
            longitudLinea = longitudDeseada - caracteresEscritos;
        }

        // Calcula el inicio y fin del sector actual
        sectorInicio = caracteresEscritos;
        sectorFin = sectorInicio + longitudLinea;

        // Inserta el patrón en una posición aleatoria dentro del sector
        if (sectorFin < longitudDeseada) {
            int posicionInsercion = sectorInicio + rand() % (longitudLinea + 1);
            for (int i = sectorInicio; i < sectorFin; i++) {
                if (i == posicionInsercion) {
                    archivo << "patron"; // Inserta el patrón
                }
                char caracter;
                int tipoCaracter = rand() % 3; // 0: Mayúscula, 1: Minúscula, 2: Número
                if (tipoCaracter == 0) {
                    caracter = 'A' + rand() % 26; // Mayúscula
                } else if (tipoCaracter == 1) {
                    caracter = 'a' + rand() % 26; // Minúscula
                } else {
                    caracter = '0' + rand() % 10; // Número
                }
                archivo << caracter;
            }
            if (posicionInsercion == sectorFin) {
                archivo << "patron"; // Inserta el patrón al final del sector
            }
        } else {
            // Si el sector se desborda, simplemente agrega caracteres sin inserción de patrón
            for (int i = sectorInicio; i < longitudDeseada; i++) {
                char caracter;
                int tipoCaracter = rand() % 3; // 0: Mayúscula, 1: Minúscula, 2: Número
                if (tipoCaracter == 0) {
                    caracter = 'A' + rand() % 26; // Mayúscula
                } else if (tipoCaracter == 1) {
                    caracter = 'a' + rand() % 26; // Minúscula
                } else {
                    caracter = '0' + rand() % 10; // Número
                }
                archivo << caracter;
            }
        }

        archivo << endl; // Agregar un salto de línea
        caracteresEscritos += longitudLinea;
    }

    archivo.close();
    if (sector < 1 || sector > 10) {
        cerr << "El valor de 'sector' debe estar en el rango de 1 a 10." << endl;
        return 1;
    }

    ifstream archivoEntrada(nombreArchivo);

    if (!archivoEntrada) {
        cerr << "No se pudo abrir el archivo de entrada." << endl;
        return 1;
    }

    string contenidoArchivo((istreambuf_iterator<char>(archivoEntrada)), (istreambuf_iterator<char>()));
    archivoEntrada.close();

    int totalCaracteres = contenidoArchivo.size();
    int inicioSector = ((sector - 1) * totalCaracteres) / 10;
    int finSector = (sector * totalCaracteres) / 10;

    string nuevoContenido = contenidoArchivo.substr(0, inicioSector);

    for (int i = 0; i < repeticiones; i++) {
        nuevoContenido += patronAInsertar;
    }

    nuevoContenido += contenidoArchivo.substr(inicioSector, finSector - inicioSector);
    nuevoContenido += contenidoArchivo.substr(finSector);

    ofstream archivoSalida(nombreArchivo);

    if (!archivoSalida) {
        cerr << "No se pudo abrir el archivo de salida." << endl;
        return 1;
    }

    archivoSalida << nuevoContenido;
    archivoSalida.close();

    //cout << "El archivo se ha modificado exitosamente." << endl;
    
    return 0;
}
