#include <string>
#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>

template<typename Data=int>
class Transaction{
private:
    std::time_t date;
    std::string sender;
    std::string receiver;
    Data data;

public:
    Transaction(){
        this->date = std::time(0);
        this->sender = "";
        this->receiver = "";
    };

    Transaction(std::string _sender, std::string _receiver, Data _data )
    : date(std::time(0)), sender(_sender), receiver(_receiver), data(_data) {}


    // get information of the transaction in a string format
    std::string get(){
        return this->sender + ", " + this->receiver + ", " + sstr(this->data) + ", " + static_cast<std::string>(std::ctime(&(this->date))) ;
    }

    // Show formatted information from a transaction
    friend std::ostream &operator<<( std::ostream &output, const Transaction& _transaction ) {
        output << "Sender: " << _transaction.sender << ", Receiver: " << _transaction.receiver << ", Data: " << _transaction.data << ", Date: " << std::ctime(&_transaction.date);
        return output;
    }
private:
    // Transforms any data type with the << overloaded into a string equivalent
    std::string sstr(Data _data){
        std::ostringstream sstr;
        sstr << std::dec << _data ;
        return sstr.str();
    }

};