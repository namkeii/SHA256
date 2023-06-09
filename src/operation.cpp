#include "../include/operation.h"
#include "../include/sha.h"

/* Defining opeartions */
/***********************/

//Shift right operation
unsigned int SHR(unsigned int word, unsigned int n){
    word = word>>n; return word;
}

//Rotate right operation
unsigned int ROTR(unsigned int word, unsigned int n){
    word = (word>>n) | (word << (32-n)); return word;
}

//Adding two numbers
unsigned int ADD(unsigned int word1, unsigned int word2){
    //unsigned int sum = (unsigned int)((word1 + 0l + word2) % MOD);
    long long sum = (unsigned int)((word1 + 0l + word2));
    //std::cout << "2tadd: " << toBinary(word1,32) << " " << toBinary(word2,32) << std::endl;
    //std::cout << toBinary(sum,32) << std::endl;
    return sum;
}

//Adding three numbers
unsigned int ADD(unsigned int word1, unsigned int word2, unsigned int word3){
    unsigned int sum = (unsigned int)((word1 + 0l + word2) % MOD);
    sum = (unsigned int)((sum + 0l + word3) % MOD);
    return sum;
}

//Adding four numbers
unsigned int ADD(unsigned int word1, unsigned int word2, unsigned int word3, unsigned int word4){
    unsigned int sum = (unsigned int)((word1 + 0l + word2) % MOD);
    sum = (unsigned int)((sum + 0l + word3) % MOD);
    sum = (unsigned int)((sum + 0l + word4) % MOD);
    return sum;
}

//Xor of two numbers
unsigned int XOR(unsigned int word1, unsigned int word2){
    unsigned int x = word1 ^ word2; return x;
}

//Xor of three numbers
unsigned int XOR(unsigned int word1, unsigned int word2, unsigned int word3){
    unsigned int x = word1 ^ word2 ^ word3; return x;
}

//lowersigma0
unsigned int s0(unsigned int word){
    unsigned int ts1 = ROTR(word, 7);
    unsigned int ts2 = ROTR(word, 18);
    unsigned int ts3 = SHR(word, 3);
    return XOR(ts1, ts2, ts3);
}

//lowersigma1
unsigned int s1(unsigned int word){
    unsigned int ts1 = ROTR(word, 17);
    unsigned int ts2 = ROTR(word, 19);
    unsigned int ts3 = SHR(word, 10);
    return XOR(ts1, ts2, ts3);
}

//uppersigma0
unsigned int S0(unsigned int word){
    unsigned int ts1 = ROTR(word, 2);
    unsigned int ts2 = ROTR(word, 13);
    unsigned int ts3 = ROTR(word, 22);
    return XOR(ts1, ts2, ts3);
}

//uppercasesigma1
unsigned int S1(unsigned int word){
    unsigned int ts1 = ROTR(word, 6);
    unsigned int ts2 = ROTR(word, 11);
    unsigned int ts3 = ROTR(word, 25);
    return XOR(ts1, ts2, ts3);
}

//choice
unsigned int CH(unsigned int word1, unsigned int word2, unsigned int word3){
    unsigned int temp = 1;
	unsigned int ch = 0;
	for(int i_ch =0; i_ch <32; i_ch++){
		if ((temp&word1) == 0){ ch = (ch|(word3&temp)); }
		else{ ch = (ch|(word2&temp)); }
		temp = (temp << 1);
	}
    return ch;
}

//majority
unsigned int MAJ(unsigned int word1, unsigned int word2, unsigned int word3){
    unsigned int maj = 0;
    unsigned int zero = 0, one = ~zero;
    unsigned int temp = 1;
    unsigned int tempMaj = 3;
    for(int i_maj = 0; i_maj < 31; i_maj++){
        unsigned int sum = (word1&temp)+(word2&temp)+(word3&temp);
        sum = (sum >> i_maj);
        if(sum<=1){ maj = (maj|(zero&temp)); }
        else{ maj = (maj|(one&temp)); }
        temp = (temp<<1);
        tempMaj = (tempMaj<<1);
    }
    temp=temp>>1; tempMaj=tempMaj>>1;word1=word1>>1;
    word2=word2>>1;word3=word3>>1;
    unsigned int sum = (word1&temp)+(word2&temp)+(word3&temp);
    sum = (sum >> 30);
    if(sum<=1){ temp = temp<<1;maj = (maj|(zero&temp)); }
    else{ temp=temp<<1; maj = (maj|(one&temp)); }
    return maj;
}

