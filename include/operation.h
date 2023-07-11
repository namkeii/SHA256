#pragma once

/*Operations*/
/************/
const long long MOD = 4294967296;

//shift right
unsigned int SHR(unsigned int, unsigned int);

//rotate right
unsigned int ROTR(unsigned int, unsigned int);

//addition
unsigned int ADD(unsigned int, unsigned int);
unsigned int ADD(unsigned int, unsigned int, unsigned int);
unsigned int ADD(unsigned int, unsigned int, unsigned int, unsigned int);

//Xor
unsigned int XOR(unsigned int, unsigned int);
unsigned int XOR(unsigned int word1, unsigned int word2, unsigned int word3);

//Sigma
unsigned int s0(unsigned int);
unsigned int s1(unsigned int);
unsigned int S0(unsigned int);
unsigned int S1(unsigned int);

//Choice
unsigned int CH(unsigned int, unsigned int, unsigned int);

//Majority
unsigned int MAJ(unsigned int, unsigned int, unsigned int);