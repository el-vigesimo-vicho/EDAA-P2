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

public:
    FMIndexSearch() {}

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

    int count(string T, string p) {
        if (constructIndex(T)) {
            return displayOccurrences(p);
        }
        return -1;
    }

    int displayOccurrences(const string& query) {
        size_t m = query.size();
        size_t occs = sdsl::count(fm_index, query.begin(), query.end());
        return occs;
    }
};

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Usage " << argv[0] << " <text_file> <pattern>" << endl;
        return 1;
    }

    FMIndexSearch fmSearch;
    fmSearch.count(argv[1], argv[2]);

    return 0;
}

