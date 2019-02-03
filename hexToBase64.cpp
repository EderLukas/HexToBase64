/*
 * source code: hexToBase64.cpp
 * title:       Hex to Base64 Converter
 * description: This programm lets the user convert a string of
 *              hex numbers into a string of Base64 characters.
 * Author:      Lukas Eder
 * date:        03.02.2019
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

void bit_shift(int &i, unsigned int &tmp_hex, vector<unsigned int> &hex_cache, int &index){
    if (i == 0) {
        tmp_hex = tmp_hex|hex_cache.at(index);
        tmp_hex<<=4;
    } else if ( i == 1) {
        tmp_hex = tmp_hex|hex_cache.at(index);
        tmp_hex<<=4;
    } else {
        tmp_hex += hex_cache.at(index);
    }
}

void binaryConvertionToBase64(vector<unsigned int> &hex_cache,
                              const unsigned int &mask,
                              void printBase64(unsigned int &letter)) {

    printf("\nYour convertion is: ");

    int cache_size = hex_cache.size();
    int index = 0;
    unsigned int tmp_hex = 0;
    int iter_rest = cache_size % 3;
    int iter_rep = cache_size / 3;

    if (!iter_rest) {
        // HEX number is devidable by 3, no extra iterations to get full input
        do{
            for (int i = 0; i < 3; i++) {
                bit_shift(i, tmp_hex, hex_cache, index);
                iter_rep--;
                index++;
            }
            unsigned int b64 = tmp_hex&mask;
            printBase64(b64);
            b64 = (tmp_hex>>=6)&mask;
            printBase64(b64);

        }while (iter_rep != 0);

    } /*else if (iter_rest) {
        // HEX number is not devidable by 3, extra iterations to get full input
        do{
            for (int i = 0; i < 3; i++) {
                bit_shift(i, tmp_hex, hex_cache, index);
                iter_rep--;
                index++;
            }
            unsigned int b64 = tmp_hex&mask;
            printBase64(b64);
            b64 = (tmp_hex>>=6)&mask;
            printBase64(b64);

        }while (iter_rep != 0);
        while(iter_rest) {
            bit_shift(iter_rest, tmp_hex, hex_cache, index);
            index++;
        }
        unsigned int b64 = tmp_hex&mask;
        printBase64(b64);
        b64 = (tmp_hex>>=6)&mask;
        printBase64(b64);
    }

    printf("\n\n");*/
}

int main () {
    vector<unsigned int> hex_cache;
    vector<unsigned int> inverted_hex_cache;
    const unsigned int mask = 0x3F;
    vector<unsigned int> user_input;

    getUserInput(user_input);
    binaryConvertionToBase64(user_input, mask, printBase64Char);
}
