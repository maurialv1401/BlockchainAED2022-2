#include "block.h"

std::string Block::get_hash(){
    return this->hash;
}

std::string Block::get_prev_hash(){
    return this->prev_hash;
}

std::string Block::get_transaction(){
    return this->transaction;
}

int Block::get_nonce(){
    return this->nonce;
}

int Block::get_size(){
    return this->size;
}

void Block::set_nonce(int nonce){
    this->nonce = nonce;
}

void Block::set_prev_hash(std::string _prev){
    this->prev_hash = _prev;
}

void Block::set_precision(int _precision){
    this->precision = _precision;
}

void Block::set_max_transactions(int _max){
    this->max_transactions = _max;
}

void Block::add_transaction(std::string _transaction){
    if (this->size == this->max_transactions){
        std::cout << "Block is full" << std::endl;
        this->mine();
    } else {
        std::cout << "Transaction Added: " << _transaction << std::endl;
        this->transaction += _transaction;
        this->size++;
    }
}

void Block::mine(){
    std::string _hash = this->calculate_hash();
    while(_hash.substr(0, this->precision) != std::string(this->precision, '0')){
        this->nonce++;
        _hash = this->calculate_hash();
    }
    this->hash = _hash;
}

std::string Block::calculate_hash(){
    std::string _hash = sha256(this->prev_hash + this->transaction + std::to_string(this->nonce));
    return _hash;
}

