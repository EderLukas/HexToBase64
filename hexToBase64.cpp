/* Hex to Base64 converter
 * Lukas Eder, 26.01.2019
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

void getUserInput(string &user_input) {
    printf("\nPlease enter your hex code: ");
    getline(cin, user_input);
}

void convertInputToHex (const string &user_input, vector<unsigned int> &hex_cache) {
    for(const char &pos : user_input) {
        if (pos >= 48 && pos <= 57) {
            hex_cache.push_back(pos-'0');
        }
        else if (pos == 65 || pos == 97) {
            hex_cache.push_back(10);
        } else if (pos == 66|| pos == 98) {
            hex_cache.push_back(11);
        } else if (pos == 67|| pos == 99) {
            hex_cache.push_back(12);
        } else if (pos == 68|| pos == 100) {
            hex_cache.push_back(13);
        } else if (pos == 69|| pos == 101) {
            hex_cache.push_back(14);
        } else if (pos == 70|| pos == 102) {
            hex_cache.push_back(15);
        }
    }
}

void invertCache(const vector<unsigned int> &hex_cache, vector<unsigned int> &inverted_hex_cache) {
    unsigned int size_of_cache = hex_cache.size();
    for (int i = size_of_cache - 1; i >= 0; i--) {
        inverted_hex_cache.push_back(hex_cache.at(i));
    }
}

void printBase64Char(unsigned int &letter){
    cout << letter << endl;
    if (letter <= 25) {
        //printf("%c", letter+65);
    } else if (letter >= 26 || letter <= 51) {
        //printf("%c", letter+71);
    } else if(letter >= 52 || letter <= 61) {
        //printf("%c", letter-4);
    } else if (letter == 62) {
        //cout << '+';
    } else if (letter == 63) {
        //cout << '/';
    }
}

void binaryConvertionToBase64(vector<unsigned int> &hex_cache,
                              const unsigned int &mask,
                              void printBase64(unsigned int &letter)) {

    int cache_size = hex_cache.size();
    if (cache_size % 3 != 0) {
        int delimiter = cache_size % 3;
        for (int i = 0; i < delimiter; i++) {
            hex_cache.insert(hex_cache.begin(), 0);
        }
    }

    int iterations_left = cache_size;
    int index = 0;
    unsigned int tmp_hex = 0;

    printf("\nYour convertion is: ");

    do {
        for (int i = 0; i < 3; i++) {
            if (i == 0) {
                tmp_hex += 265*hex_cache.at(index);
            } else if ( i == 1) {
                tmp_hex += 16*hex_cache.at(index);
            } else {
                tmp_hex += hex_cache.at(index);
            }
            iterations_left--;
            index++;
        }

        unsigned int b64 = tmp_hex&mask;
        printBase64(b64);

        do {
            b64 = (tmp_hex>>=6)&mask;
            printBase64(b64);
        } while (tmp_hex<<6 != 0);
    } while(iterations_left != 0);
    printf("\n\n");
}


int main () {
    vector<unsigned int> hex_cache;
    vector<unsigned int> inverted_hex_cache;
    const unsigned int mask = 0x3F;
    string user_input;

    getUserInput(user_input);
    convertInputToHex(user_input, hex_cache);
    //invertCache(hex_cache, inverted_hex_cache);
    for (unsigned int i : hex_cache) {
        cout << i;
    }
    binaryConvertionToBase64(hex_cache, mask, printBase64Char);
}
