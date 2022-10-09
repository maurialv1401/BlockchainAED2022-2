#include <utility>

#include "block.h"

// implement template and smart pointers'
template<typename Data=int>
class Blockchain {
private:
    // mutables
    int size; // size of blockchain
    Block<Data> * current;
    // fixed
    Block<Data> * genesis;
    int precision;
    int max_transactions;
    
public:
    Blockchain(){
        this->genesis = new Block<Data>("000", 0);
        this->precision = 3;
        this->max_transactions = 4;
        this->size = 1;
        this->current = new Block<Data>(this->max_transactions);
        this->genesis->next = this->current;
        this->current->set_prev_hash(this->genesis->get_hash());
        this->current->set_precision(this->precision);
    };

    // insert must accept a class Transaction with his elements
    void insert(Transaction<Data>* transaction){
        // *insert every element in a tree for later searches*
        // <>inserting...</>
        this->current->add_transaction(transaction);
        if (this->current->get_size() == this->max_transactions){
            // if current block is full, create a new one based on the previous hash
            auto prev_hash = this->current->get_hash();
            this->current->next = new Block<Data>(this->max_transactions);
            this->current = this->current->next;
            this->current->set_prev_hash(prev_hash);
            this->current->set_precision(this->precision);
            this->size++;
        }
    }

    // cascade function starts when a transaction tried to be added into the blockchain
    void modify(int indx, Transaction<Data>* transaction){
        if (indx > this->size) return;
        
        auto temp = this->genesis->next;
        int n = 1;
        while (n != indx){
            temp = temp->next;
            n++;
        }
        temp->set_max_transactions(this->max_transactions + 1);
        temp->add_transaction(transaction);
        auto new_prev_hash = temp->mine();
        n=0;
        // modificamos hasta el ultimo bloque
        // verificar si es necesario "&& temp->next->get_size() == this->max_transactions"
        while(temp->next != nullptr){
            temp = temp->next;
            temp->set_prev_hash(new_prev_hash);
            temp->mine();
            new_prev_hash = temp->get_hash();
            n++;
        }
        std::cout << "Cantidad de Bloques Modificados: " << n <<std::endl;
    }
    // metodo para agregar elementos al bloque hasta llenarlo y luego unirlo a la cadena
    // no usado por actualizacion del sistema.
    void add_block(Block<Data>* block){
        block->set_precision(this->precision);
        block->set_prev_hash(this->current->get_hash());
        block->mine();
        // unimos los bloques
        this->current->next = block;
        // actualizamos el ultimo bloque
        this->current = block;
        this->size++;
    }

    // Iteramos por los bloques e imprimimos sus datos
    void print_chain(){
        int n =1;
        Block<Data> * temp = this->genesis->next;
        while(temp != nullptr){
            std::cout << "Block # " << n << ": "<< std::endl;
            std::cout << "Hash: " << temp->get_hash() << std::endl;
            std::cout << "Prev Hash: " << temp->get_prev_hash() << std::endl;
//            std::cout << "Merkle Root: " << current->get_merkleroot() << std::endl;
            std::cout << "Transactions: " << temp->get_transactions() << std::endl;
            std::cout << "Nonce: " << temp->get_nonce() << std::endl;
            std::cout << "Size: " << temp->get_size() << std::endl;
            std::cout << "----------------" << std::endl;
            temp = temp->next;
            n++;
        }
    }
    /*
    bool find_transaction(std::string _transaction){
        Block * current = this->genesis->next;
        while(current != nullptr){
            if (current->verify(_transaction)){
                return true;
            }
            current = current->next;
        }
        return false;
    }*/

    int size_block() const{
        return this->size;
    }

    ~Blockchain(){
        Block<Data> * current_ = this->genesis;
        while(current_ != nullptr){
            Block<Data> * temp = current_;
            current_ = current_->next;
            delete temp;
        }
    }
};