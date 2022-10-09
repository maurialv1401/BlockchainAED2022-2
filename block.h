#include <utility>
#include "merkle.h"
#include "transaction.h"

// use hash & smart pointers
// implement template
template<typename Data=int>
class Block {
private:
// asignar a cada bloque los valores 
// ***  prev_hash, precision y max_transactions  ***
    std::string prev_hash;
    std::string hash;
    std::string transactions_value;
    std::vector<Transaction<Data>*> transactions;
    std::vector<std::string> transactions_data;
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
        this->transactions.emplace_back(new Transaction<Data>());
        this->transactions_data.emplace_back("Genesis Block");
        this->transactions.shrink_to_fit();
        this->nonce = 0;
        this->precision = 2;
        this->size = -1;
        this->mine();
    };

    std::string get_hash();
    std::string get_prev_hash();
    std::string get_transactions();
    int get_nonce() const;
    int get_size() const;
    std::string get_merkleroot() const;
    //void set_nonce(int nonce);
    void set_precision(int _precision);
    void set_max_transactions(int _max);
    void set_prev_hash(std::string _prev);
//    void add_transaction(const std::string& transaction);
    void add_transaction(Transaction<Data>* transaction);
    std::string mine();
    std::string calculate_hash();
    // ** bool verify(std::string _transaction); // find in the tree the hashed transaction

    Block * next;
    merkle::MerkleNode * root;

    ~Block(){
        for (const auto & t: this->transactions){
            delete t;
        }
    }
};

template<typename Data>
std::string Block<Data>::get_hash(){
    return this->hash;
}

template<typename Data>
std::string Block<Data>::get_prev_hash(){
    return this->prev_hash;
}

template<typename Data>
int Block<Data>::get_nonce() const{
    return this->nonce;
}

template<typename Data>
int Block<Data>::get_size() const{
    return this->size;
}

template<typename Data>
std::string Block<Data>::get_merkleroot() const{
    return this->root->hash();
}

template<typename Data>
void Block<Data>::set_prev_hash(std::string _prev){
    this->prev_hash = std::move(_prev);
}

template<typename Data>
void Block<Data>::set_precision(int _precision){
    this->precision = _precision;
}

template<typename Data>
void Block<Data>::set_max_transactions(int _max){
    this->max_transactions = _max;
}

template<typename Data>
void Block<Data>::add_transaction(Transaction<Data>* _transaction){
    if (this->size == this->max_transactions){
        std::cout << "Block is full" << std::endl;
        // if this->hash or this->root have not been defined then:
        this->root = merkle::Build(this->transactions_data);

        this->mine();
    } else {
        std::cout << "Transaction Added: " << *_transaction << std::endl;
        this->transactions.push_back(_transaction);
        this->transactions_data.push_back(_transaction->get());
        this->transactions_value += _transaction->get();
        this->size++;
        if (this->size == this->max_transactions){
            std::cout << "Block is full" << std::endl;
            this->root = merkle::Build(this->transactions_data);
            this->mine();
        }
    }
}

template<typename Data>
std::string Block<Data>::mine(){
    if (this->size == 0) return " ";
    std::string _hash = this->calculate_hash();
    while(_hash.substr(0, this->precision) != std::string(this->precision, '0')){
        this->nonce++;
        _hash = this->calculate_hash();
    }
    this->hash = _hash;
    return this->hash;
}

template<typename Data>
std::string Block<Data>::calculate_hash(){
    std::string _hash = sha256(this->prev_hash + this->transactions_value + std::to_string(this->nonce));
    return _hash;
}

template<typename Data>
std::string Block<Data>::get_transactions() {
    std::string cadena;
    for (const auto & t: this->transactions){
        std::ostringstream  sstr;
        sstr<<std::dec<<*t;
        cadena+= "\n" + sstr.str();
    }
    return cadena;
}
