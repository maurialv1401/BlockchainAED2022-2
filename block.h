#include "sha256.h"
#include <string>
#include <iostream>


// use hash & smart pointers
// implement template
class Block {
private:
    std::string prev_hash;
    std::string hash;
    std::string transaction; // need to be a tree of transactions
    // add timestamp
    int nonce;
    int size;
    int precision;
    int max_transactions;

public:
    Block() = default;
    Block(int max){
        this->max_transactions = max;
        this->size = 0;
        this->nonce = 0;
        this->next = nullptr;
    };
    // genesis constructor
    Block(std::string _prev_hash, int max){
        this->prev_hash = _prev_hash;
        this->max_transactions = max;
        this->transaction = "Genesis Data";
        this->nonce = 0;
        this->precision = 2;
        this->size = 0;
        this->mine();
    };
    std::string get_hash();
    std::string get_prev_hash();
    std::string get_transaction();
    int get_nonce();
    int get_size();
    void set_nonce(int nonce);
    void set_precision(int _precision);
    void set_max_transactions(int _max);
    void set_prev_hash(std::string _prev);
    void add_transaction(std::string transaction);
    void mine();
    std::string calculate_hash();
    bool verify(std::string _transaction); // find in the tree the hashed transaction

    Block * next;
};