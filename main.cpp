#include "blockchain.h"

int main(){
    Blockchain * chain = new Blockchain();
    Block *block = new Block(4);
    block->add_transaction("Maria,Pedro,100"); block->add_transaction("Pedro,Jose,150");
    block->add_transaction("Maria,Juan,300"); block->add_transaction("Juan,Jose,50");
    
    Block *block2 = new Block(4);
    block2->add_transaction("Juan,Pedro,100"); block2->add_transaction("Pedro,Maria,150");
    block2->add_transaction("Pedro,Jose,300"); block2->add_transaction("Maria,Jose,50");

    chain->add_block(block);
    chain->add_block(block2);

    chain->print_chain();
    return 0;
}