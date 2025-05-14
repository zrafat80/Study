#include <iostream>
#include <string>
using namespace std;

string incrementBinary(string tape) {
    int i = tape.length() - 1;
    while (i >= 0 && tape[i] == '1') {
        tape[i] = '0';
        i--;
    }
    if (i >= 0) tape[i] = '1';
    else tape = '1' + tape;
    return tape;
}

int main() {
    string tape;
    cout << "Enter binary number: ";
    cin >> tape;
    string result = incrementBinary(tape);
    cout << "After increment: " << result << endl;
    return 0;
}
