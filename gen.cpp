#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>

void generarArchivoConRepeticiones(std::string nombreArchivo, int n, std::string x, int y) {
    std::ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return;
    }

    std::string caracteres = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    int longitudCaracteres = caracteres.length();
    int longitudX = x.length();
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (int i = 0; i < n; i++) {
        // Agregar salto de línea aleatorio
        if (std::rand() % 10 == 0) {
            archivo << '\n';
        }

        char caracterAleatorio = caracteres[std::rand() % longitudCaracteres];
        archivo << caracterAleatorio;

        // Randomizar la posición del patrón
        if (std::rand() % (n / y) == 0) {
            int posicionPatron = std::rand() % (n - longitudX);
            archivo.seekp(posicionPatron);
            archivo << x;
        }
    }

    archivo.close();
    std::cout << "Archivo generado: " << nombreArchivo << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Uso: " << argv[0] << " <nombre_archivo> <longitud_texto> <cadena> <repeticiones>" << std::endl;
        return 1;
    }

    std::string nombreArchivo = argv[1];
    int longitudTexto = std::stoi(argv[2]);
    std::string cadena = argv[3];
    int repeticiones = std::stoi(argv[4]);

    generarArchivoConRepeticiones(nombreArchivo, longitudTexto, cadena, repeticiones);

    return 0;
}
