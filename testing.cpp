#include <iostream>
#include <bitset>
#include <string>

using namespace std;

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

// Convert hex to binary
bitset<64> hexToBitset64(const string& hexStr) {
    bitset<64> result(stoull(hexStr, nullptr, 16));
    return result;
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

int main() {

    //Below is the L16 value and K16 Key
    bitset<32> testInput(string("01000011010000100011001000110100"));
    bitset<48> testKey(string("110010110011110110001011000011100001011111110101"));
    bitset<48> expanded = expansionPermutation(testInput);
    //Working!!! (i think) cout << "L16 expanded: " << expanded << endl;
    bitset<48> xored = expanded ^ testKey;
    //Working!!! (i think) cout << "L16 XOR K16: " << xored << endl;
    bitset<32> sBoxOutput = sBoxSubstitution(xored);
    //Working!!! (i think) cout << "S-Box output: " << sBoxOutput << endl;
    bitset <32> output2 = pPermutation(sBoxOutput);
    //Working!!! (i think) cout << "Final output: " << output2 << endl;
    
    return 0;
}

