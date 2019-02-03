/* Hex to Base64 converter
 * Lukas Eder, 26.01.2019
 */

#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>
using namespace std;

void getUserInput(vector<unsigned int> &user_input) {
    printf("\nPlease enter your hex code (finish with '0x3B'): ");
    unsigned int input_elem = 0;
    while (1) {
        scanf("%x", &input_elem);
        if (input_elem == 0x3B) {
            while((getchar()) != '\n');
            break;
        }
        user_input.push_back(input_elem);
        // TODO delete debug code
        cout << "input: " << input_elem << endl;
        while((getchar()) != '\n');
    }
}

void invertCache(const vector<unsigned int> &hex_cache, vector<unsigned int> &inverted_hex_cache) {
    cout << "hello";
    unsigned int size_of_cache = hex_cache.size();
    for (int i = size_of_cache - 1; i >= 0; i--) {
        inverted_hex_cache.push_back(hex_cache.at(i));
    }
}

void printBase64Char(unsigned int &letter){
    if (letter <= 25) {
        printf("%c", letter+65);
    } else if (letter >= 26 || letter <= 51) {
        printf("%c", letter+71);
    } else if(letter >= 52 || letter <= 61) {
        printf("%c", letter-4);
    } else if (letter == 62) {
        cout << '+';
    } else if (letter == 63) {
        cout << '/';
    }
}

void binaryConvertionToBase64(vector<unsigned int> &hex_cache,
                              const unsigned int &mask,
                              void printBase64(unsigned int &letter)) {

    int cache_size = hex_cache.size();
    // TODO delete debug code
    cout << "cache size: " << cache_size << endl;
    if (cache_size % 3 != 0) {
        int delimiter = cache_size % 3;
        for (int i = 0; i < delimiter; i++) {
            hex_cache.insert(hex_cache.begin(), 0);
        }
    }

    // TODO delete debug code
    cout << "hex_cache: ";
    for (unsigned int &hex : hex_cache){
        cout << hex;
    }
    cout << endl;

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
    vector<unsigned int> user_input;

    getUserInput(user_input);
    invertCache(user_input, inverted_hex_cache);
    binaryConvertionToBase64(inverted_hex_cache, mask, printBase64Char);
}
