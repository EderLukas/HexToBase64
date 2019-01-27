/* Hex to Base64 converter
 * Lukas Eder, 26.01.2019
 */

 #include <iostream>
 #include <vector>
 using namespace std;

 void askForInput(unsigned char *string_to_convert) {
     cout << "\nPlease provide your input: ";
     cin >> string_to_convert;
 }

 vector<unsigned char> processOutput(unsigned char *string_to_convert) {
     // TODO implement convertion
     vector<unsigned char> result;
     for (unsigned char i=0; i <= sizeof(string_to_convert); i++) {
         result.push_back(string_to_convert[i]);
     }
     return result;
 }

void showOutput(vector<unsigned char> &converted_string) {
    // FIXME is giving the ascii code right now
    for (unsigned char &elem : converted_string) {
        printf("%d\n", elem);
    }
}

void askForAnotherConvertion(int &convert_again) {
    string prog_rep;
    cout << "Would you like to do another convertion? (Y/n): ";
    cin.ignore();
    getline(cin >> hex, prog_rep);

    while(true) {
        if (prog_rep == "n") {
            convert_again = 0;
            break;
        } else if (prog_rep == "y" || prog_rep == "Y" || prog_rep.empty()){
            convert_again = 1;
            break;
        }
        cout << "\nPlease answer with y or n: ";
        getline(cin >> hex, prog_rep);
    }
}

 int main () {
    int convert_again = 0;
    unsigned char string_to_convert[255];
    vector<unsigned char> converted_string;

    cout << "\n#######################\n"
         << "Hex to Base64 converter\n"
         << "#######################\n\n";

    do {
        askForInput(string_to_convert);
        converted_string = processOutput(string_to_convert);
        showOutput(converted_string);
        askForAnotherConvertion(convert_again);
    } while (convert_again);

    cout << "\nbye!" << endl;
 }
