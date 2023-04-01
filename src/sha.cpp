#include "../include/sha.h"

/* Message */
/***********/

//Convert to binary
std::string toBinary(unsigned int num, int binarySize){
    std::string revBin = "";
    while(num!=0){ revBin += std::to_string(num%2); num /= 2; }
    while(revBin.size() != binarySize){ revBin += '0'; }
    for(int i_rev = 0; i_rev < revBin.size()/2; i_rev++){
        char temp = revBin[i_rev];
        revBin[i_rev] = revBin[revBin.size()-1-i_rev];
        revBin[revBin.size()-1-i_rev] = temp;
    }
    return revBin;
}

//Convert to hexademical
std::string toHexadecimal(std::string binary) {
    std::unordered_map<std::string, char> lookup = {
        {"0000", '0'}, {"0001", '1'}, {"0010", '2'}, {"0011", '3'},
        {"0100", '4'}, {"0101", '5'}, {"0110", '6'}, {"0111", '7'},
        {"1000", '8'}, {"1001", '9'}, {"1010", 'a'}, {"1011", 'b'},
        {"1100", 'c'}, {"1101", 'd'}, {"1110", 'e'}, {"1111", 'f'}
    };
    std::string hexadecimal;
    for (size_t i = 0; i < binary.length(); i += 4) {
        std::string group = binary.substr(i, 4);
        hexadecimal += lookup[group];
    }
    return hexadecimal;
}

//create the binary string
std::string msgToBinary(std::string msg){
    std::string bin = "";
    for(int i_msg = 0; i_msg < msg.size(); i_msg++){ bin += toBinary((int)msg[i_msg], 8); }
    //Padding
    unsigned int bsize = bin.size();
    int numberOfZero = 512 - (bin.size()+1+64)%512;
    bin += '1';
    while(numberOfZero != 0){ bin += '0'; numberOfZero--; }
    bin += toBinary(bsize,64);
    return bin;
}