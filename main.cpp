#include "blockchain.h"
#include <iostream>

 
using std::string;
using std::cout;
using std::endl;
using Data = float;
 
int main()
{
    Blockchain<Data> * chain = new Blockchain<Data>();

    chain->insert(new Transaction<Data>("Maria","Pedro",1.5)); chain->insert(new Transaction<Data>("Pedro","Jose",150));
    chain->insert(new Transaction<Data>("Maria","Juan",300)); chain->insert(new Transaction<Data>("Juan","Jose",50));

    chain->insert(new Transaction<Data>("Juan","Pedro",100)); chain->insert(new Transaction<Data>("Pedro","Maria",150));
    chain->insert(new Transaction<Data>("Pedro","Jose",30000)); chain->insert(new Transaction<Data>("Maria","Jose",50));

    std::cout<<"ORIGINAL BLOCKCHAIN"<<std::endl;
    chain->print_chain();

    chain->insert(new Transaction<Data>("Juan","Pedro",100)); chain->insert(new Transaction<Data>("Pedro","Maria",150));
    chain->insert(new Transaction<Data>("Pedro","Jose",30000)); chain->insert(new Transaction<Data>("Maria","Jose",50));


    chain->modify(1,new Transaction<Data>("Jose","Maria",15000));

    std::cout<<"MODIFIED BLOCKCHAIN"<<std::endl;
    chain->print_chain();

    delete chain;
    return 0;
}

