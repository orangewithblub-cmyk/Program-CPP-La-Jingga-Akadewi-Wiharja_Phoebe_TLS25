#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

// Membalik string tanpa fungsi reverse bawaan
string my_reverse(const string& s) {
    string res = "";
    for (int i = s.length() - 1; i >= 0; i--) {
        res += s[i];
    }
    return res;
}

// Cek apakah huruf vokal
bool isVowel(char c) {
    c = tolower(c);
    return c == 'a' || c == 'i' || c == 'u' || c == 'e' || c == 'o';
}

// Fungsi enkripsi: mesin misterius (satu arah)
string make_password(const string& word) {
    if (word.empty()) return "";
    string no_vowel = "";
    for (char c : word) {
        if (!isVowel(c)) no_vowel += c;
    }
    string reversed = my_reverse(no_vowel);
    int ascii = (int)word[0];
    // Sisipkan kode ASCII di tengah
    int mid = reversed.length() / 2;
    string ascii_str = to_string(ascii);
    string result = reversed.substr(0, mid) + ascii_str + reversed.substr(mid);
    return result;
}

// Fungsi bantu: dekripsi parsial
void parse_password(const string& sandi) {
    cout << "Mencoba mendekripsi sandi: " << sandi << endl;
    bool found = false;
    // Coba kode ASCII 2 digit atau 3 digit di tengah sandi
    for (int len = 2; len <= 3; ++len) {
        int mid = sandi.length() / 2;
        int left = mid - (len % 2 == 0 ? len/2 : len/2);
        if (left < 0 || left + len > sandi.length()) continue;
        string ascii_str = sandi.substr(left, len);
        int ascii = 0;
        try {
            ascii = stoi(ascii_str);
        } catch (...) {
            continue;
        }
        if (ascii < 65 || ascii > 122) continue; // hanya huruf A-z
        // Buat string tanpa kode ASCII
        string s_wo_ascii = sandi.substr(0, left) + sandi.substr(left+len);
        // Balikkan string
        string no_vowel = my_reverse(s_wo_ascii);
        char first_char = (char)ascii;
        cout << "Kemungkinan kata asli (tanpa vokal): ";
        cout << first_char << no_vowel.substr(1) << endl;
        found = true;
    }
    if (!found) {
        cout << "Tidak ditemukan kemungkinan kode ASCII yang valid di tengah sandi." << endl;
    }
}

int main() {
    cout << "== MESIN MISTERIUS PEMBUAT & PEMBACA SANDI ==" << endl;
    cout << "1. Buat sandi dari kata\n2. Pecahkan sandi menjadi kata parsial\n";
    cout << "Pilih menu (1/2): ";
    int menu;
    cin >> menu;
    cin.ignore();
    if (menu == 1) {
        string kata;
        cout << "Masukkan kata asli: ";
        getline(cin, kata);
        cout << "Sandi hasil mesin: " << make_password(kata) << endl;
    } else if (menu == 2) {
        string sandi;
        cout << "Masukkan sandi: ";
        getline(cin, sandi);
        parse_password(sandi);
    } else {
        cout << "Menu tidak valid.\n";
    }
    return 0;
}