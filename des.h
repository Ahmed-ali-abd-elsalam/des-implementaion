#ifndef DES_H
#define DES_H
#include<bits/stdc++.h>
#include<fstream>
using namespace std;
string HexToBin(char s);
bitset<64> intialPermutation(bitset<64>plainText);
bitset<64> inverseIntialPermutation(bitset<64>plainText);
bitset<64> expansion(bitset<64> rightSide);
void round(bitset<64> plaintext,bitset<64>key);
#endif