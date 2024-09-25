#include <iostream>
#include <bitset>
#include <string>
#include <vector>
#include <iomanip>

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

// Initial permutation (IP)
const int IP[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

// Expansion permutation (E)
const int E[48] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
};

// S-boxes
const int S[8][4][16] = {
    { /* S1 */
        14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
        0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8, 
        4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
        15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13
    },
    { /* S2 */
        15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
        3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
        0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
        13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9

    },
    { /* S3 */
        10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
        13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
        13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
        1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12
    },
    { /* S4 */
        7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
        13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
        10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
        3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14
    },
    { /* S5 */
        2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
        14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
        4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
        11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3
    },
    { /* S6 */
        12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14 , 7, 5, 11,
        10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
        9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
        4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13
    },
    { /* S7 */
        4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
        13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
        1, 4, 11, 13, 12, 3, 7, 14, 10, 15 ,6, 8, 0, 5, 9, 2,
        6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12
    },
    { /* S8 */
        13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
        1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
        7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
        2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11
    }
};

// Permutation after S-box substitution (P)
const int P[32] = {
    16, 7, 20, 21,
    29, 12, 28, 17,
    1, 15, 23, 26,
    5, 18, 31, 10,
    2, 8, 24, 14,
    32, 27, 3, 9,
    19, 13, 30, 6,
    22, 11, 4, 25
};

// Final Permutation/Inverse IP (FP)
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

// Convert binary to hex
string bitset64ToHex(const bitset<64>& bs) {
    stringstream ss;
    unsigned long long num = bs.to_ullong();
    ss << hex << uppercase << setw(16) << setfill('0') << num;
    return ss.str();
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

// Define Permutations
bitset<64> initialPermutation(bitset<64> input) {
    bitset<64> output;
    for (int i = 0; i < 64; ++i) {
        output[i] = input[IP[i] - 1];
    }
    return output;
}

bitset<48> expansionPermutation(bitset<32> halfBlock) {
    bitset<48> expanded;
    for (int i = 0; i < 48; ++i) {
        expanded[i] = halfBlock[E[i] - 1];
    }
    return expanded;
}

bitset<32> sBoxSubstitution(bitset<48> input) {
    string outputBits = "";
    for (int i = 0; i < 8; ++i) {
        bitset<6> blockValue;
        bitset<2> row;
        bitset<4> column;
        int startingBit = i * 6;
        

        for (int j = 0; j < 6; ++j) {
            blockValue[5 - j] = input[47 - startingBit - j];
        }

        row[1] = blockValue[5];
        row[0] = blockValue[0];

        for(int k = 0; k < 4; k++){
            column[3 - k] = blockValue[4 - k];
        }

        long rowNum = row.to_ulong();
        long colNum = column.to_ulong();
        unsigned long long sBoxValue = S[i][rowNum][colNum];
        bitset<4> subbedBlock(sBoxValue);
        outputBits.append(subbedBlock.to_string());
    }
    bitset<32> output(outputBits);
    return output;
}

bitset<32> pPermutation(bitset<32> input) {
    bitset<32> output;
    for (int i = 0; i < 32; ++i) {
        output[31 - i] = input[32 - P[i]];
    }
    return output;
}

bitset<64> finalPermutation(bitset<64> input) {
    bitset<64> output;
    for (int i = 0; i < 64; ++i) {
        output[i] = input[FP[i] - 1];
    }
    return output;
}

bitset<32> fFunction(bitset<32> rightHalf, bitset<48> roundKey) {
    bitset<48> expanded = expansionPermutation(rightHalf);
    bitset<48> xorResult = expanded ^ roundKey;
    bitset<32> substituted = sBoxSubstitution(xorResult);
    bitset<32> permuted = pPermutation(substituted);
    return permuted;
}


bitset<64> desEncryption(bitset<64> plainText, bitset<64> key){
    string combinedHalves;
    // Perform initial permutation
    bitset<64> permutedBlock = initialPermutation(plainText);

    // Split the permuted block into left and right halves
    bitset<32> leftHalf = bitset<32>(permutedBlock.to_ullong() >> 32);
    bitset<32> rightHalf = bitset<32>(permutedBlock.to_ullong() & 0xFFFFFFFF);
    
    // Generate the 56-bit key for scheduling
    bitset<56> key56 = keyPermutation(key);

    for (int round = 0; round < 16; round++){
        //Generate the subKey for the round
        bitset<48> subKeyValue = subKey(key56, round);

        // Apply the F function
        bitset<32> fResult = fFunction(rightHalf, subKeyValue);
        
        // Update the left and right halves
        bitset<32> newLeftHalf = rightHalf;
        rightHalf = leftHalf ^ fResult;
        leftHalf = newLeftHalf;
        combinedHalves = rightHalf.to_string() + leftHalf.to_string();
    }

    // Combine the final left and right halves into a single 64-bit block
        bitset<64> finalBlock(combinedHalves);

    // Perform the final permutation (inverse initial permutation)
    return finalPermutation(finalBlock);
}

int main() {
    // Hex values for the DES parameters
    string hexPlaintext, hexKey;
    cout << "Enter plaintext: ";
    cin >> hexPlaintext;
    cout << "Enter key: ";
    cin >> hexKey;
    
    bitset<64> plainText = hexToBitset64(hexPlaintext);
    bitset<64> key = hexToBitset64(hexKey);
    
    bitset<64> encrypted = desEncryption(plainText, key);
    
    cout << "Encrypted Data: " << bitset64ToHex(encrypted) << endl;
    return 0;
}