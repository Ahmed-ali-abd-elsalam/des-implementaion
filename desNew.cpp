#include <bits/stdc++.h>
#ifdef __GNUC__
# define __rdtsc __builtin_ia32_rdtsc
#else
# include<intrin.h>
#endif

using namespace std;
typedef unsigned long long u64;

u64* converted = new u64 [214748364];
int convertedSize = 0;

u64 readDESInputhex(const char *data){
    u64 value =0;
    for(int i=0; i<16 ; i++){
        char c = data[i];
        if(c>='0' && c<='9'){
            value |= (u64) (c-'0') << ((15-i)<<2);
        }
        else if(c>='A' && c<='F'){
            value |= (u64) (c-'A' +10) << ((15-i)<<2);
        }
        else if(c>='a' && c<='f'){
         value |= (u64) (c-'a' +10) << ((15-i)<<2);
    }
}
 return value;
}

u64 messagePlainHelper (int x , u64 d , int i){
    d |= (u64)(x) << ((7-i) << 3);
    return d;
}

void readMessagePlain (){
    // array of characters
    char* array1 = new char [214748364];
    int array_length = 0;
    // filling the array
    char ch;
    ifstream file;
    file.open("plain_text.txt" , ios::in);
    int c = 0;
    while (!file.eof()){
        file >> noskipws >> ch;
        array1[c++] = ch;
    }
    array_length = c;
    int eights =ceil( ((double) (array_length))/8);
    // 2d array filling  with ascii values of 8 characters for each row
    int arr [eights][8];
    int counter = 0;
    for (int i = 0 ; i < eights ; i++){
        for (int j = 0 ; j < 8 ; j++){
            arr[i][j]= int( array1[counter++]);
        }
    }
    // filling the u64 int array called converted
    convertedSize = eights;
    for (int i = 0 ; i < convertedSize; i++){
            u64 value = 0;
        for (int j = 0 ; j < 8; j++){
            value = messagePlainHelper(arr[i][j], value, j);
        }
        converted[i] = value;
        value = 0;
    }
}

u64 intialPermutation(u64 plainText)
{
    const int IP_t[64] = {58, 50, 42, 34, 26, 18, 10, 2,
                          60, 52, 44, 36, 28, 20, 12, 4,
                          62, 54, 46, 38, 30, 22, 14, 6,
                          64, 56, 48, 40, 32, 24, 16, 8,
                          57, 49, 41, 33, 25, 17, 9, 1,
                          59, 51, 43, 35, 27, 19, 11, 3,
                          61, 53, 45, 37, 29, 21, 13, 5,
                          63, 55, 47, 39, 31, 23, 15, 7};
    u64 result = 0;
    for (int i = 0; i < 64; i++){
        result |= (plainText >> (64 - IP_t[i]) & 1) << 64 - (i + 1);
    }
    return result;
}

u64 inverseIntialPermutation(u64 plainText)
{
    const int IIP_t[64] = {40, 8, 48, 16, 56, 24, 64, 32,
                           39, 7, 47, 15, 55, 23, 63, 31,
                           38, 6, 46, 14, 54, 22, 62, 30,
                           37, 5, 45, 13, 53, 21, 61, 29,
                           36, 4, 44, 12, 52, 20, 60, 28,
                           35, 3, 43, 11, 51, 19, 59, 27,
                           34, 2, 42, 10, 50, 18, 58, 26,
                           33, 1, 41, 9, 49, 17, 57, 25};
    u64 result = 0;
    for (int i = 0; i < 64; i++)
    {
        result |= (plainText >> (64 - IIP_t[i]) & 1) << 64 - (i + 1);
    }
    return result;
}

u64 permutationChoiceKey1(u64 key)
{
    const int pc_1[56] = {57, 49, 41, 33, 25, 17, 9,
                          1, 58, 50, 42, 34, 26, 18,
                          10, 2, 59, 51, 43, 35, 27,
                          19, 11, 3, 60, 52, 44, 36,
                          63, 55, 47, 39, 31, 23, 15,
                          7, 62, 54, 46, 38, 30, 22,
                          14, 6, 61, 53, 45, 37, 29,
                          21, 13, 5, 28, 20, 12, 4};
    u64 result = 0;
    for (int i = 0; i < 56; i++)
    {
        result |= ((key >> (64 - pc_1[i])) & 1) << 64 - (i+1);
    }
    return result;
}

u64 permutationChoiceKey2(u64 key)
{
    const int pc_2[48] = {14, 17, 11, 24, 1, 5,
                          3, 28, 15, 6, 21, 10,
                          23, 19, 12, 4, 26, 8,
                          16, 7, 27, 20, 13, 2,
                          41, 52, 31, 37, 47, 55,
                          30, 40, 51, 45, 33, 48,
                          44, 49, 39, 56, 34, 53,
                          46, 42, 50, 36, 29, 32};
    u64 result = 0;
    for (int i = 0; i < 48; i++)
    {
        result |= (key >> (64 - pc_2[i]) & 1) << 64 - (i + 1);
    }
    return result;
}

u64 expansion(u64 rightSide)
{
    const int E_t[48] = {32, 1, 2, 3, 4, 5, // expantion table
                         4, 5, 6, 7, 8, 9,
                         8, 9, 10, 11, 12, 13,
                         12, 13, 14, 15, 16, 17,
                         16, 17, 18, 19, 20, 21,
                         20, 21, 22, 23, 24, 25,
                         24, 25, 26, 27, 28, 29,
                         28, 29, 30, 31, 32, 1};
    u64 result = 0;
    for (int i = 0; i < 48; i++)
    {
        result |= (rightSide >> (64 - E_t[i]) & 1) << 64 - (i + 1);
    }
    return result;
}

u64 permutaion(u64 rightSide)
{
    const int P[32] = {16, 7, 20, 21,
                       29, 12, 28, 17,
                       1, 15, 23, 26,
                       5, 18, 31, 10,
                       2, 8, 24, 14,
                       32, 27, 3, 9,
                       19, 13, 30, 6,
                       22, 11, 4, 25};
    u64 result = 0;
    for (int i = 0; i < 32; i++)
    {
        result |= (rightSide >> (64 - P[i]) & 1) << 64 - (i + 1);
    }
    return result;
}

u64 sbox(u64 rightSide)
{
    int S[8][4][16] = {// S-box
                       {
                           {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
                           {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
                           {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
                           {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}},
                       {{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
                        {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
                        {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
                        {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}},
                       {{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
                        {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
                        {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
                        {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}},
                       {{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
                        {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
                        {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
                        {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}},
                       {{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
                        {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
                        {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
                        {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}},
                       {{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
                        {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
                        {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
                        {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}},
                       {{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
                        {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
                        {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
                        {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}},
                       {{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
                        {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
                        {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
                        {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}}};
    u64 out = 0;
    rightSide = rightSide>>(64-48);
    for (int i = 0; i < 8; i++)
    {
        u64 idx = (rightSide >> ((7 - i) * 6)) & 0x3f;
        idx = ((idx >> 1) & 15) |
              ((idx & 1) << 4) |
              (idx & 0x20);
        out = out|(u64(S[i][idx >> 4][idx & 15])<< ((7 - i) * 4));
    }
    out =out<<32;
    return out;
}

u64 leftshift(u64 keyhalf, int index)
{
    keyhalf = keyhalf>>(64-28);
    int leftShiftTable[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
    // store bit        shift left      set rightmost bits      clear leftmost bits
    int stored = keyhalf >> (28 - leftShiftTable[index]);
    keyhalf = (keyhalf << leftShiftTable[index]) | stored;
    keyhalf = keyhalf<<(64-28);
    return keyhalf;
}

u64 feistelFunction(u64 rightside,u64 key){
    u64 result = 0;
    result = expansion(rightside);
    result = result^ key;
    result= sbox(result);
    result = permutaion(result);
    return result;
}

u64 singleRound(u64 plaintext, u64 key){
    // initial permutation and plain text split
    plaintext = intialPermutation(plaintext);
    u64 leftText = (plaintext >> 32)<<32;
    u64 rightText = (plaintext << 32);
    u64 cypherText = 0;
    // key permutation and split
    key = permutationChoiceKey1(key);
    u64 keyLeft = (key >>(64-28))<<(64-28);
    u64 keyRight = (key >> (64 - 56)) << (64 - 28);
    key = 0;

    for (int i = 0; i < 16; i++){
        keyLeft = leftshift(keyLeft, i);
        keyRight = leftshift(keyRight, i);
        key = key | keyLeft;
        key = key | (keyRight>>28);
        key = permutationChoiceKey2(key);
        cypherText = feistelFunction(rightText,key);
        cypherText = cypherText ^ leftText;
        leftText = rightText;
        rightText = cypherText;
        key =0;
    }
    cypherText = rightText;
    rightText = leftText;
    leftText = cypherText;
    cypherText = 0;
    cypherText = cypherText | (leftText);
    cypherText = cypherText | (rightText>>32);
    cypherText = inverseIntialPermutation(cypherText);
    return cypherText;
}

void outputBinary(u64 cypher){
    // shift then output to file instead of cout
    for(int i=0;i<64;i++){
        cout<<((cypher >>(63-i))&1);
    }
}

void outputHex(u64 cypher){
    // shift then output to file instead of cout
    int value =0;
    char c;
    for(int i=0;i<16;i++){
        value = (cypher>>((15-i)<<2))&0xf;
        if(value<10){
            cout<<value;
        }else{
            c = char('A'+(value-10));
            cout<<c;
        }
    }
}

int main()
{
    //Read key input as 16 hex characters
    char s[16]; 
    ifstream file;
    file.open("key.txt");
    file >> s;
    u64 key = readDESInputhex(s);
    // Plain Text 
    readMessagePlain();
    u64 encrypted [convertedSize]={0}; 
    long long t1=__rdtsc();
    cout<<singleRound(converted[0],key);
    for(int i=0;i<convertedSize;i++){
        encrypted[i] = singleRound(converted[i],key);
    //     outputBinary(encrypted[i]);
    //     outputHex(encrypted[i]);
    }
    long long t2=__rdtsc();
    printf("Cycles: to decrypt the file %lld\n", t2-t1);



}
