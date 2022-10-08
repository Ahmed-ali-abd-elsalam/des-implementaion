#ifndef DES_H
#define DES_H
#include<bits/stdc++.h>
#include<fstream>
using namespace std;
int charToInt(char c);
string decToBinary(int n);
bitset<64> intialPermutation(bitset<64>plainText);
void round(bitset<64> plaintext,bitset<64>key);
#endif