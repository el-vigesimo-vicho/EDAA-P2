#include <sdsl/suffix_arrays.hpp>
#include <string>
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace sdsl;
using namespace std;

class FMIndexSearch {
private:
    string index_suffix = ".fm9";
    csa_wt<wt_huff<rrr_vector<127> >, 512, 1024> fm_index;
    size_t max_locations;
    size_t post_context;
    size_t pre_context;

public:
    FMIndexSearch(size_t max_loc=5, size_t post_ctx=10, size_t pre_ctx=10)
        : max_locations(max_loc), post_context(post_ctx), pre_context(pre_ctx) {}

    bool constructIndex(const string& file) {
        string index_file = file + index_suffix;
        if (load_from_file(fm_index, index_file)) {
            return true;
        }

        ifstream in(file);
        if (!in) {
            cout << "ERROR: File " << file << " does not exist. Exit." << endl;
            return false;
        }

        cout << "No index " << index_file << " located. Building index now." << endl;
        construct(fm_index, file.c_str(), 1); // generate index
        store_to_file(fm_index, index_file);  // save it
        return true;
    }

    

    void search() {
        std::string primeraLinea;
        std::ifstream archivo("patron.txt");
        if (archivo.is_open()) {
        std::getline(archivo, primeraLinea);
        archivo.close();
        } else {
        // Manejar el caso en que no se pueda abrir el archivo
        std::cerr << "No se pudo abrir el archivo: " << std::endl;
        }
        //cout << "Index construction complete, index requires " << size_in_mega_bytes(fm_index) << " MiB." << endl;
        //out << "Input search terms and press Ctrl-D to exit." << endl;
        //string prompt = "\e[0;32m>\e[0m ";
        //cout << prompt;
        string query =primeraLinea;
        displayOccurrences(query);
        //cout << endl;
    }

    void displayOccurrences(const string& query) {
        size_t m = query.size();
        size_t occs = sdsl::count(fm_index, query.begin(), query.end());
        //cout << "# of occurrences: " << occs << endl;
        /*
        if (occs > 0) {
            cout << "Location and context of first occurrences: " << endl;
            auto locations = locate(fm_index, query.begin(), query.begin() + m);
            sort(locations.begin(), locations.end());
            for (size_t i = 0, pre_extract = pre_context, post_extract = post_context; i < min(occs, max_locations); ++i) {
                cout << setw(8) << locations[i] << ": ";
                if (pre_extract > locations[i]) {
                    pre_extract = locations[i];
                }
                if (locations[i] + m + post_extract > fm_index.size()) {
                    post_extract = fm_index.size() - locations[i] - m;
                }
                auto s = extract(fm_index, locations[i] - pre_extract, locations[i] + m + post_extract - 1);
                string pre = s.substr(0, pre_extract);
                s = s.substr(pre_extract);
                if (pre.find_last_of('\n') != string::npos) {
                    pre = pre.substr(pre.find_last_of('\n') + 1);
                }
                cout << pre;
                cout << "\e[1;31m";
                cout << s.substr(0, m);
                cout << "\e[0m";
                string context = s.substr(m);
                cout << context.substr(0, context.find_first_of('\n')) << endl;
            }
        }
        */
    }
};

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Usage " << argv[0] << " text_file [max_locations] [post_context] [pre_context]" << endl;
        return 1;
    }

    size_t max_locations = 5;
    size_t post_context = 10;
    size_t pre_context = 10;
    if (argc >= 3) max_locations = atoi(argv[2]);
    if (argc >= 4) post_context = atoi(argv[3]);
    if (argc >= 5) pre_context = atoi(argv[4]);

    FMIndexSearch fmSearch(max_locations, post_context, pre_context);
    if (fmSearch.constructIndex(argv[1])) {
        fmSearch.search();
    }

    return 0;
}

