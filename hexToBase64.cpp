/*
 * source code: hexToBase64.cpp
 * title:       Hex to Base64 Converter
 * description: This programm lets the user convert a
 *              hex number into a string of Base64 characters.
 *              The hex number is defined in the main function.
 * Author:      Lukas Eder
 * date:        03.02.2019
 */

 #include <iostream>
 #include <vector>
 using namespace std;

void convert(unsigned int &hex, const unsigned int &mask,
             vector<unsigned int> &converted_hex) {

    converted_hex.push_back(hex&mask);
    do {
        converted_hex.push_back((hex>>=6)&mask);
    } while (hex<<6 != 0);
}

void createBase64(vector<unsigned int> &converted_hex, vector<char> &base_64){
    char letter;
    for (unsigned int &element : converted_hex) {
        if (element <= 25) {
            letter = element+65;
            base_64.push_back(letter);
        } else if (element >= 26 || element <= 51) {
            letter = element+71;
            base_64.push_back(letter);
        } else if(element >= 52 || element <= 61) {
            letter = element-4;
            base_64.push_back(letter);
        } else if (element == 62) {
            base_64.push_back('+');
        } else if (element == 63) {
            base_64.push_back('/');
        }
    }
}

void displayConvertion(vector<char> &base_64) {
    printf("\nYour convertion is: ");
    for(char &i : base_64){
        printf("%c", i);
    }
    printf("\n\n");
}

 int main () {
    unsigned int hex = 0x492;
    const unsigned int mask = 0x3F;
    vector<unsigned int> converted_hex;
    vector<char> base_64;

    convert(hex, mask, converted_hex);
    createBase64(converted_hex, base_64);
    // erase 0x of hex number
    base_64.pop_back();

    displayConvertion(base_64);
 }
