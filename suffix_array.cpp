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

int count(const string &text, const string &pattern, const vector<int> &suffixArray) {
    int n = text.length();
    int m = pattern.length();
    int firstOccurrence = searchSubstring(text, pattern, suffixArray);

    if (firstOccurrence == -1) {
        return 0; // El patrón no se encuentra en el texto.
    }

    // Buscar la última ocurrencia del patrón.
    int lastOccurrence = searchSubstring(text, pattern, suffixArray);

    // Contar las ocurrencias entre la primera y la última ocurrencia.
    int count = 0;
    for (int i = firstOccurrence; i <= lastOccurrence; i++) {
        if (text.compare(suffixArray[i], m, pattern) == 0) {
            count++;
        }
    }

    return count;
}

int main() {
    string text = "banana";
    vector<int> suffixArray = buildSuffixArray(text);

    string pattern = "a";
    int occurrences = count(text, pattern, suffixArray);

    cout << "El patrón '" << pattern << "' se encuentra " << occurrences << " veces en el texto." << endl;

    return 0;
}
