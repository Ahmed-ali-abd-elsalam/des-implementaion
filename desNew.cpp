#include <bits/stdc++.h>
#include <math.h>
using namespace std;

typedef unsigned long long u64;

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
    for (int i = 0; i < 64; i++)
    {
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
    for (int i = 0; i < 64; i++)
    {
        result |= (key >> (64 - pc_1[i]) & 1) << 64 - (i + 1);
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
    for (int i = 0; i < 64; i++)
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
    for (int i = 0; i < 64; i++)
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
    for (int i = 0; i < 64; i++)
    {
        result |= (rightSide >> (64 - P[i]) & 1) << 64 - (i + 1);
    }
    return result;
}

// u64 sbox(u64 rightSide);
u64 leftshift(u64 keyhalf, int index)
{
    int leftShiftTable[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
    // store bit        shift left      set rightmost bits      clear leftmost bits
    int stored = keyhalf >> (28 - leftShiftTable[index]);
    keyhalf = (keyhalf << leftShiftTable[index]) | stored;
    keyhalf = (keyhalf << (64 - 28)) >> (64 - 28);
    return keyhalf;
}
u64 round(u64 plaintext, u64 key)
{

    // intitaal permutation and plain text split
    plaintext = intialPermutation(plaintext);
    u64 leftText = plaintext >> 32;
    u64 rightText = (plaintext << 32) >> 32;
    u64 cypherText = 0;

    // key permutation and split
    key = permutationChoiceKey1(key);
    u64 keyLeft = (key >> 28);
    u64 keyRight = (key << (64 - 28)) >> (64 - 28);

    for (int i = 0; i < 16; i++)
    {
        cypherText = expansion(rightText);
        keyLeft = leftshift(keyLeft,i);
        keyRight = leftshift(keyRight,i);
        key = key | (keyLeft << 28);
        key = key | keyRight;
        key = permutationChoiceKey2(key);
        cypherText = cypherText ^ key;
        // cypherText = sbox(cypherText);
        cypherText = permutaion(cypherText);
        cypherText = cypherText ^ leftText;
        leftText = rightText;
        rightText = cypherText;
    }
    
    cypherText = 0;
    cypherText = cypherText | (leftText << 32);
    cypherText = cypherText | rightText;
    cypherText = inverseIntialPermutation(cypherText);
    return cypherText;
}

int main(){

}