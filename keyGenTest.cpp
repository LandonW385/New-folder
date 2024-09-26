#include <iostream>
#include <bitset>
#include <string>
#include <vector>

using namespace std;

// Key initial permutation (PC1)
const int PC1[56] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
};

// Key final permutation (PC2)
const int PC2[48] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

// Key schedule shift values (ROTATE_SHIFTS)
const int ROTATE_SHIFTS[16] = {
    1, 1, 2, 2, 2, 2, 2, 2,
    1, 2, 2, 2, 2, 2, 2, 1
};

// Convert hex to binary
bitset<64> hexToBitset64(const string& hexStr) {
    bitset<64> result(stoull(hexStr, nullptr, 16));
    return result;
}

// Permute key to 56 bits
bitset<56> keyPermutation(const bitset<64>& key) {
    bitset<56> pc1Key;
    for (int i = 0; i < 56; i++) {
        pc1Key[55 - i] = key[63 - (PC1[i] - 1)];
    }
    return pc1Key;
}

//Schedule shifts and permute to subkeys
bitset<48> subKey(bitset<56> key, int round) {
    static bitset<28> C; // Make C static
    static bitset<28> D; // Make D static

if (round == 0) { // Initialize C and D only on the first round
    C = bitset<28>(key.to_ullong() >> 28); // Left 28 bits
    D = bitset<28>(key.to_ullong() & 0xFFFFFFF); // Right 28 bits
}

// Rotate C and D by the number of shifts specified for this round
for (int i = 0; i < ROTATE_SHIFTS[round]; i++) {
    C = (C << 1) | (C >> 27); // Rotate left
    D = (D << 1) | (D >> 27); // Rotate left
}

// Combine C and D into a 56-bit key
bitset<56> combinedKey = bitset<56>((C.to_ullong() << 28) | D.to_ullong());

// Generate subkey using PC2 permutation
bitset<48> subKey;
for (int i = 0; i < 48; i++) {
    subKey[47 - i] = combinedKey[55 - (PC2[i] - 1)];
}

return subKey;
}



int main() {
    vector <bitset<48>> subKeyV;

    string hexKey = "133457799BBCDFF1";
    bitset<64> key = hexToBitset64(hexKey);

    bitset<56> pc1Key = keyPermutation(key);
    for (int i = 0; i < 16; i++) {
        bitset<48> subKeys = subKey(pc1Key, i);
        subKeyV.push_back(subKeys);
    }

    

    return 0;
}

