#include <iostream>
#include <bitset>
#include <string>

using namespace std;

const int FP[64] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};

// Convert hex to binary
bitset<64> hexToBitset64(const string& hexStr) {
    bitset<64> result(stoull(hexStr, nullptr, 16));
    return result;
}

bitset<64> finalPermutation(bitset<64> cipherText) {
    bitset<64> output;
    for (int i = 0; i < 64; ++i) {
        output[i] = cipherText[FP[i] - 1];
    }
    return output;
}

int main() {

    bitset<64> cipherText = hexToBitset64("85E813540F0AB405");
    cout << cipherText << endl;
    bitset<64> combinedHalves = finalPermutation(cipherText);
    cout << combinedHalves << endl;

    return 0;
}

