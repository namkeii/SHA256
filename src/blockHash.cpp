#include "../include/blockHash.h"

unsigned int toInteger(std::string bin){
    unsigned int power = 0;
    int index = bin.size()-1;
    unsigned int integer = 0;
    while(index>=0){ 
        integer += (bin[index]-'0')*((unsigned int)pow(2,power));
        power++; index--;
    }
    return integer;
}

Block::Block(std::string msg, unsigned int *h){
    for(int i_h = 0; i_h < 8; i_h++){ hash[i_h] = h[i_h]; }
    this->msg = msg;
    hp = h;
}

void Block::makeSchedule(){
    //Filling first 15 words
    for(int i_msg = 0; i_msg < 512; i_msg+=32){
        std::string word = msg.substr(i_msg,32);
        schedule.push_back(toInteger(word));
    }
    //Making the remaining words
    for(int i_sc = 16; i_sc < 64; i_sc++){
        unsigned int word = ADD(s1(schedule[i_sc-2]),schedule[i_sc-7],s0(schedule[i_sc-15]),schedule[i_sc-16]);
        schedule.push_back(word);
    }
}

void Block::compress(){
    for(int i_comp = 0; i_comp < 64; i_comp++){
        unsigned T1 = ADD(S1(hash[4]), CH(hash[4], hash[5], hash[6]), hash[7], K[i_comp]);
        T1 = ADD(T1,schedule[i_comp]);
        unsigned T2 = ADD(S0(hash[0]), MAJ(hash[0], hash[1], hash[2]));
        //move down
        for(int i = 8; i > 0; i--){
            hash[i] = hash[i-1];
        }
        //update
        hash[0] = ADD(T1,T2);
        hash[4] = ADD(hash[4],T1);
    }
    //finalize
    for(int i_h = 0; i_h < 8; i_h++){ hp[i_h] = ADD(hp[i_h],hash[i_h]); }
}

