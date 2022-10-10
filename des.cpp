#include "des.h"

/*   *************** remaining
			1 S-box
			2 permutation
			3 left shift
			4 xors
			5 key side splitting
			6 reading key file and binary file at the same time
			7 optimization
			 */
using namespace std;
string BinToHex(string s)
{
	string hex = "";
	for (int i = 0; i < s.size(); i += 4)
	{
		string k = "";
		for (int j = i; j < i + 4; j++)
			k += s[j];
		if (k == "0000")
			hex += '0';
		else if (k == "0001")
			hex += '1';
		else if (k == "0010")
			hex += '2';
		else if (k == "0011")
			hex += '3';
		else if (k == "0100")
			hex += '4';
		else if (k == "0101")
			hex += '5';
		else if (k == "0110")
			hex += '6';
		else if (k == "0111")
			hex += '7';
		else if (k == "1000")
			hex += '8';
		else if (k == "1001")
			hex += '9';
		else if (k == "1010")
			hex += 'A';
		else if (k == "1011")
			hex += 'B';
		else if (k == "1100")
			hex += 'C';
		else if (k == "1101")
			hex += 'D';
		else if (k == "1110")
			hex += 'E';
		else if (k == "1111")
			hex += 'F';
	}
	return hex;
}
string HexToBin(char s)
{
	string bin = "";
	
		switch (s)
		{
		case '0':
			bin += "0000";
			break;
		case '1':
			bin += "0001";
			break;
		case '2':
			bin += "0010";
			break;
		case '3':
			bin += "0011";
			break;
		case '4':
			bin += "0100";
			break;
		case '5':
			bin += "0101";
			break;
		case '6':
			bin += "0110";
			break;
		case '7':
			bin += "0111";
			break;
		case '8':
			bin += "1000";
			break;
		case '9':
			bin += "1001";
			break;
		case 'A':
		case 'a':
			bin += "1010";
			break;
		case 'B':
		case 'b':
			bin += "1011";
			break;
		case 'C':
		case 'c':
			bin += "1100";
			break;
		case 'D':
		case 'd':
			bin += "1101";
			break;
		case 'E':
		case 'e':
			bin += "1110";
			break;
		case 'F':
		case 'f':
			bin += "1111";
			break;
		}
	return bin;
}


// every module or block should be an function
// initial permutation hopefully done
bitset<64> intialPermutation(bitset<64>plainText){
		//  Initial Permutation (IP)
	const int IP_t[64] = {58, 50, 42, 34, 26, 18, 10, 2, // intital permutation table
						  60, 52, 44, 36, 28, 20, 12, 4,
						  62, 54, 46, 38, 30, 22, 14, 6,
						  64, 56, 48, 40, 32, 24, 16, 8,
						  57, 49, 41, 33, 25, 17, 9, 1,
						  59, 51, 43, 35, 27, 19, 11, 3,
						  61, 53, 45, 37, 29, 21, 13, 5,
						  63, 55, 47, 39, 31, 23, 15, 7};
	string s="";
	for(int i=0;i<64;i++){
		s+="0";
	}
	bitset<64> result(s);
	// for debugging
/* 			cout<<(plainText<<(64-10))<<endl;
			cout<<((plainText<<(64-10))>>63)<<endl;
			cout<<(((plainText<<(64-10))>>63)<<7-1)<<endl; */

	for(int i=0;i<64;i++){
		result = result|(((plainText<<(64-IP_t[i]))>>63)<<(i));
	}
	return result;
}
bitset<64> inverseIntialPermutation(bitset<64>plainText){
	const int IIP_t[64] = {40, 8, 48, 16, 56, 24, 64, 32,
						 39, 7, 47, 15, 55, 23, 63, 31,
						 38, 6, 46, 14, 54, 22, 62, 30,
						 37, 5, 45, 13, 53, 21, 61, 29,
						 36, 4, 44, 12, 52, 20, 60, 28,
						 35, 3, 43, 11, 51, 19, 59, 27,
						 34, 2, 42, 10, 50, 18, 58, 26,
						 33, 1, 41, 9, 49, 17, 57, 25};
	string s="";
	for(int i=0;i<64;i++){
		s+="0";
	}
	bitset<64> result(s);
	for(int i=0;i<64;i++){
		result = result|(((plainText<<(64-IIP_t[i]))>>63)<<(i));
	}
	return result;
}
bitset<64> permutationChoiceKey1(bitset<64> key){
	const int pc_1[56] = {57, 49, 41, 33, 25, 17, 9,
						1, 58, 50, 42, 34, 26, 18,
						10, 2, 59, 51, 43, 35, 27,
						19, 11, 3, 60, 52, 44, 36,
						63, 55, 47, 39, 31, 23, 15,
						7, 62, 54, 46, 38, 30, 22,
						14, 6, 61, 53, 45, 37, 29,
						21, 13, 5, 28, 20, 12, 4};
	string s="";
	for(int i=0;i<64;i++){
		s+="0";
	}
	bitset<64> result(s);
		for(int i=0;i<64;i++){
		result = result|(((key<<(64-pc_1[i]))>>63)<<(i));
	}
	return result;
}
bitset<64> permutationChoiceKey2(bitset<64> key){
	const int pc_2[48] = {14, 17, 11, 24, 1, 5,
						  3, 28, 15, 6, 21, 10,
						  23, 19, 12, 4, 26, 8,
						  16, 7, 27, 20, 13, 2,
						  41, 52, 31, 37, 47, 55,
						  30, 40, 51, 45, 33, 48,
						  44, 49, 39, 56, 34, 53,
						  46, 42, 50, 36, 29, 32};
	string s="";
	for(int i=0;i<64;i++){
		s+="0";
	}
	bitset<64> result(s);
		for(int i=0;i<64;i++){
		result = result|(((key<<(64-pc_2[i]))>>63)<<(i));
	}
	return result;
}
bitset<64> expansion(bitset<64> rightSide){
		const int E_t[48] = {32, 1, 2, 3, 4, 5, // expantion table
						 4, 5, 6, 7, 8, 9,
						 8, 9, 10, 11, 12, 13,
						 12, 13, 14, 15, 16, 17,
						 16, 17, 18, 19, 20, 21,
						 20, 21, 22, 23, 24, 25,
						 24, 25, 26, 27, 28, 29,
						 28, 29, 30, 31, 32, 1};
		string s= "";
		for(int i=0;i<64;i++){
			s+="0";
		}
		// cout<<(rightSide<<(64-1))<<endl;
		// 	cout<<((rightSide<<(64-1))>>63)<<endl;
		// cout<<(((rightSide<<(64-1))>>63)<<2-1)<<endl;
	bitset<64> result(s);
	for(int i=0;i<48;i++){
			result = result|(((rightSide<<(64-E_t[i]))>>63)<<i);
	}
	return result;
}

// bitset<64> plaintext,bitset<64>key
void round(bitset<64> plaintext,bitset<64>key){
	// initial split
	string ones ="", zeros ="";
	for(int i=0;i<64/2;i++){
		ones+="1";
		zeros+="0";
	}
	string right=zeros+ones;
	string left =ones+zeros;
	bitset<64> leftText(left);
	bitset<64> rightText(left);
	cout<<leftText<<"    "<<right<<endl;
	leftText = plaintext|leftText;
	rightText = plaintext|rightText;


	// f is the input of the xor
	// rightText = leftText^F;
	// leftText = rightText

}

int main()
{
	// round();
	// this values are for debugging
	/* "0000000000000000000000000000000000000000000000000000000000000010"	2
	"0000001000000000000000000000000000000000000000000000000000000000"	58
	"0000000100000000000000000000000000000000000000000000000000000000"	57
	"0000000000000010000000000000000000000000000000000000000000000000"	50
	"0000000000000000000000000000000000000000000000000000001000000000"	10
	"0000000000000000000000000000000000000000000000000000000100000000"	9
	"0000000000000000000000000000000000000000000000000000000010000000" 	8 */
	// string z = "0000000000000000000000000000000000000000000000000000000000000001";
	// cout<<z.size()<<endl<<z.find("1")<<endl;
	// bitset<64> s("0000000000000000000000000000000000000000000000000000000000000001");
	// cout<<s<<endl;
	// cout<<intialPermutation(s);
	// cout<<inverseIntialPermutation(s);
	// cout<<expansion(s);
	// cout<<permutationChoiceKey1(s);
	// cout<<permutationChoiceKey2(s);
	ifstream read;
	read.open("trial.txt");
	ofstream write;
	write.open("binary.txt");
	string x;
	// writing biary
	string bin="";
	while (getline(read, x))
	{
		for (int i = 0; i < x.size(); i++)
		{
			bin = HexToBin(x[i]);
			// cout<<bin;
	 	if (i %16  == 0 && i > 0)
			{
				write << "\n";
				bin = "";
			}
		// 	// write string rep in file
		// 	// write<<decToBinary(let);
		// 	// write binary rep in file
		// 	bitset<8> bset(decToBinary(let));
			write << bin;
		}
	}
	read.close();
	write.close();
	read.open("binary.txt");
	write.open("cypher.txt");
	string s ="123456789";
	cout<<s.substr(4,4);
	while (getline(read, x))
	{
		for(int i=0;i<x.size();i = i+4){
			s = x.substr(i,4);
			write<<BinToHex(s);
		}
		// write << x << endl;
	}
	return 0;
}