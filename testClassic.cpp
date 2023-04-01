#include "./include/blockHash.h"
#include "./include/operation.h"
#include "./include/sha.h"
#include <iomanip>
#include <chrono>

std::string hash(std::string msg);
int main(){
    std::string msg;
    std::getline(std::cin,msg);

    //start the time
    auto start = std::chrono::high_resolution_clock::now();
    std::ios_base::sync_with_stdio(false);

    std::string fh, sh;
    //unsigned int i_h = 0;
    unsigned int i_h = 274038001;
    for(; i_h < pow(2,32); i_h++){
        std::string msg1 = msg+litEnd(toHexadecimal(toBinary(i_h,32)));
        std::cout << "NONCE " << i_h << ": ";
        fh = hash(msg1);
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

std::string hash(std::string msg){
    unsigned int hh[] = {a,b,c,d,e,f,g,h};
    std::string bmsg = msgToBinary(msg);

    for(int i = 0; i < bmsg.size(); i+=512){
        //create the block
        Block* block = new Block(bmsg.substr(i,512),hh);
        block->makeSchedule();
        block->compress();
    }
    std::string hx = "";
    for(int bb = 0; bb < 8; bb++) hx += toHexadecimal(toBinary(hh[bb],32));
    return hx;
}
