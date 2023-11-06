#include <sdsl/suffix_arrays.hpp>
#include <string>
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace sdsl;
using namespace std;

string leerArchivoSinSaltosDeLinea(const string &nombreArchivo) {
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return "";
    }

    string contenido;
    string linea;

    while (getline(archivo, linea)) {
        contenido += linea;
    }

    archivo.close();

    return contenido;
}

class FMIndexSearch {
private:
    string index_suffix = ".fm9";
    csa_wt<wt_huff<rrr_vector<127> >, 512, 1024> fm_index;

public:
    FMIndexSearch() {}

    bool constructIndex(const string& file) {
        ifstream in(file);
        if (!in) {
            cout << "ERROR: File " << file << " does not exist. Exit." << endl;
            return false;
        }

        construct(fm_index, file.c_str(), 1); // generate index
        return true;
    }

    int count(string T, string p) {
        constructIndex(T);
        return displayOccurrences(p);
    }

    int displayOccurrences(const string& query) {
        size_t m = query.size();
        size_t occs = sdsl::count(fm_index, query.begin(), query.end());
        return occs;
    }
};

int main(int argc, char** argv) {

    string nombreArchivo = "texto.txt"; // Reemplaza con el nombre de tu archivo

    string nombreArchivo2 = "patron.txt"; // Reemplaza con el nombre de tu archivo

    string patron = leerArchivoSinSaltosDeLinea(nombreArchivo2);

    FMIndexSearch fmSearch;
    cout << fmSearch.count(nombreArchivo, patron) << endl;

    return 0;
}

