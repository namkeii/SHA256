#pragma once
#include <iostream>
#include <unordered_map>
/*Constants*/

const unsigned int a = 0x6a09e667;
const unsigned int b = 0xbb67ae85;
const unsigned int c = 0x3c6ef372;
const unsigned int d = 0xa54ff53a;
const unsigned int e = 0x510e527f;
const unsigned int f = 0x9b05688c;
const unsigned int g = 0x1f83d9ab;
const unsigned int h = 0x5be0cd19;


extern std::unordered_map<std::string, char> lookup;
extern std::unordered_map<char, std::string> clookup;

/*Padding*/
/*********/

//Make the Binary String
std::string msgToBinary(std::string);

std::string toBinary(unsigned int, int);
std::string toHexadecimal(std::string binary);
std::string litEnd(std::string);