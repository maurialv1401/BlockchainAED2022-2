#include "block.h"

// implement template and smart pointers
class Blockchain {
private:
    Block * genesis;
    Block * last;
    int precision;
    int max_transactions;
    int size;
    
public:
    Blockchain(){
        this->genesis = new Block("0", 0);
        this->precision = 2;
        this->max_transactions = 4;
        this->size = 1;
        this->last = this->genesis;
    };
    void add_block(Block* block){
        block->set_precision(this->precision);
        block->set_prev_hash(this->last->get_hash());
        block->mine();
        // unimos los bloques
        this->last->next = block;
        // actualizamos el ultimo bloque
        this->last = block;
        this->size++;
    }
    void print_chain(){
        Block * current = this->genesis->next;
        while(current != nullptr){
            std::cout << "Hash: " << current->get_hash() << std::endl;
            std::cout << "Prev Hash: " << current->get_prev_hash() << std::endl;
            std::cout << "Transaction: " << current->get_transaction() << std::endl;
            std::cout << "Nonce: " << current->get_nonce() << std::endl;
            std::cout << "Size: " << current->get_size() << std::endl;
            std::cout << "----------------" << std::endl;
            current = current->next;
        }
    }
    bool find_transaction(std::string _transaction){
        Block * current = this->genesis->next;
        while(current != nullptr){
            if (current->verify(_transaction)){
                return true;
            }
            current = current->next;
        }
        return false;
    }

    int get_size(){
        return this->size;
    }

    ~Blockchain(){
        Block * current = this->genesis;
        while(current != nullptr){
            Block * temp = current;
            current = current->next;
            delete temp;
        }
    }
};