#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Suffix {
    string suff;
    int index;
};

bool compareSuffixes(const Suffix &a, const Suffix &b) {
    return a.suff < b.suff;
}

vector<int> buildSuffixArray(const string &text) {
    int n = text.length();
    vector<Suffix> suffixes(n);

    for (int i = 0; i < n; i++) {
        suffixes[i].suff = text.substr(i);
        suffixes[i].index = i;
    }

    sort(suffixes.begin(), suffixes.end(), compareSuffixes);

    vector<int> suffixArray(n);
    for (int i = 0; i < n; i++) {
        suffixArray[i] = suffixes[i].index;
    }

    return suffixArray;
}

int searchSubstring(const string &text, const string &pattern, const vector<int> &suffixArray) {
    int n = text.length();
    int m = pattern.length();
    int left = 0;
    int right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int compareResult = pattern.compare(0, m, text, suffixArray[mid], m);

        if (compareResult == 0) {
            return suffixArray[mid];
        } else if (compareResult < 0) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return -1; // El patrón no se encuentra en el texto.
}

int main() {
    string text = "banana";
    vector<int> suffixArray = buildSuffixArray(text);

    string pattern = "nan";
    int result = searchSubstring(text, pattern, suffixArray);

    if (result != -1) {
        cout << "El patrón '" << pattern << "' se encuentra en la posición " << result << " del texto." << endl;
    } else {
        cout << "El patrón '" << pattern << "' no se encuentra en el texto." << endl;
    }

    return 0;
}
