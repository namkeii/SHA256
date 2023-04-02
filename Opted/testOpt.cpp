#include "./include/blockHash.h"
#include "./include/operation.h"
#include "./include/sha.h"
#include <iomanip>
#include <chrono>
unsigned int hh[] = {a,b,c,d,e,f,g,h};
unsigned int afterHash[8];

void reset(){
    for(int i_h = 0; i_h < 8; i_h++){
        hh[i_h] = afterHash[i_h];
    }
}

void reset1(){
    hh[0] = a; hh[1] = b; hh[2] = c;
    hh[3] = d; hh[4] = e; hh[5] = f;
    hh[6] = g; hh[7] = h;
}

std::string hash(std::string msg);
std::string firstHash(std::string msg);
std::string secondHash(std::string msg);
int main(){
    std::string msg;
    std::getline(std::cin,msg);

    //start the time
    auto start = std::chrono::high_resolution_clock::now();
    std::ios_base::sync_with_stdio(false);

    std::string fh, sh;

    //first hash part 1
    std::string msg1 = msg.substr(0,128);
    std::string msg2 = msg.substr(128);
    std::string hash1 = firstHash(msg1);
    //std::cout << hash1 << std::endl;
    for(int i_h = 0; i_h < 8; i_h++){
        afterHash[i_h] = hh[i_h];
    }

    unsigned int i_h = 274048011;
    //unsigned int i_h = 274038001;
    for(; i_h < pow(2,32); i_h++){
        std::string hmsg = msg+litEnd(toHexadecimal(toBinary(i_h,32)));
        std::cout << "NONCE " << i_h << ": ";
        fh = secondHash(hmsg);
        //std::cout << fh << std::endl;
        //second hash
        //hash(fh);
        sh = hash(fh);
        sh = litEnd(sh);
        std::cout << sh << std::endl;
        bool ans = true;
        for(int j_c = 0; j_c < 10; j_c++){
            if(sh[j_c] != '0'){ans = false; break; }
        }
        if (ans){std::cout << "NONCE: " << i_h << std::endl; break; }
    }

    //stop the time
    auto end = std::chrono::high_resolution_clock::now();
    double tt = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
    tt *= 1e-9;

    std::cout << sh << std::endl;
    std::cout << "TIME TAKEN: " << std::fixed << tt << std::setprecision(9);
    std::cout << " seconds" << std::endl;
}

std::string firstHash(std::string msg){
    std::string bmsg = msgToBinary(msg);

    //create the block
    Block* block = new Block(bmsg.substr(0,512),hh);
    block->makeSchedule();
    block->compress();

    std::string hx = "";
    for(int bb = 0; bb < 8; bb++) hx += toHexadecimal(toBinary(hh[bb],32));
    return hx;
}

std::string secondHash(std::string msg){
    std::string bmsg = msgToBinary(msg);

    //create the block
    Block* block = new Block(bmsg.substr(512),hh);
    block->makeSchedule();
    block->compress();

    std::string hx = "";
    for(int bb = 0; bb < 8; bb++) hx += toHexadecimal(toBinary(hh[bb],32));
    return hx;
}

std::string hash(std::string msg){
    reset1();
    std::string bmsg = msgToBinary(msg);

    for(int i = 0; i < bmsg.size(); i+=512){
        //create the block
        Block* block = new Block(bmsg.substr(i,512),hh);
        block->makeSchedule();
        block->compress();
    }
    std::string hx = "";
    for(int bb = 0; bb < 8; bb++) hx += toHexadecimal(toBinary(hh[bb],32));
    reset();
    return hx;
}
