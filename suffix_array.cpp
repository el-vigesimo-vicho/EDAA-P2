#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

struct Suffix {
    int index;
    string suffix;
};

bool compareSuffixes(const Suffix &a, const Suffix &b) {
    return a.suffix < b.suffix;
}

vector<int> buildSuffixArray(const string &text) {
    int n = text.length();
    vector<Suffix> suffixes(n);

    for (int i = 0; i < n; i++) {
        suffixes[i].index = i;
        suffixes[i].suffix = text.substr(i);
    }

    sort(suffixes.begin(), suffixes.end(), compareSuffixes);

    vector<int> suffixArray(n);
    for (int i = 0; i < n; i++) {
        suffixArray[i] = suffixes[i].index;
    }

    return suffixArray;
}

int binarySearch(const string &text, const vector<int> &suffixArray, const string &pattern) {
    int n = text.length();
    int m = pattern.length();
    int low = 0, high = n - 1;
    int count = 0;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        auto x=suffixArray[mid];
        int result = text.compare(suffixArray[mid], m, pattern);
        if (result == 0) {
            count++;
            int left = mid - 1, right = mid + 1;
            while (left >= 0 && text.compare(suffixArray[left], m, pattern) == 0) {
                count++;
                left--;
            }
            while (right < n && text.compare(suffixArray[right], m, pattern) == 0) {
                count++;
                right++;
            }
            break;
        } else if (result < 0) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return count;
}

int count(const string &text, const string &pattern) {
    vector<int> suffixArray = buildSuffixArray(text);
    return binarySearch(text, suffixArray, pattern);
}

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


int main() {
    string nombreArchivo = "texto.txt"; // Reemplaza con el nombre de tu archivo

    string texto = leerArchivoSinSaltosDeLinea(nombreArchivo);
    string nombreArchivo2 = "patron.txt"; // Reemplaza con el nombre de tu archivo

    string patron = leerArchivoSinSaltosDeLinea(nombreArchivo2);

    int repetitions = count(texto, patron);
    //cout << "El patrón se repite " << repetitions << " veces en el texto." << endl;

    return 0;
}
