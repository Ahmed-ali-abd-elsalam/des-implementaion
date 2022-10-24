#include <bits/stdc++.h>
#ifdef __GNUC__
#define __rdtsc __builtin_ia32_rdtsc
#else
#include <intrin.h>
#endif
using namespace std;
typedef unsigned long long u64;
u64 readDESInputhex(const char *data);
u64 messagePlainHelper(int x, u64 d, int i);
void readMessagePlain(char mode);
u64 intialPermutation(u64 plainText);
u64 inverseIntialPermutation(u64 plainText);
u64 permutationChoiceKey1(u64 key);
u64 permutationChoiceKey2(u64 key);
u64 expansion(u64 rightSide);
u64 permutaion(u64 rightSide);
u64 sbox(u64 rightSide);
u64 leftshift(u64 keyhalf, int index);
u64 feistelFunction(u64 rightside, u64 key);
u64 singleRound(u64 plaintext, u64 key, char mode);
void outputPlainText(u64 cypher, char mode);

