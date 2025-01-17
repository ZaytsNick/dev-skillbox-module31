﻿#include <iostream>
#include <string>
class Toy {
public:
    Toy(const std::string& name) {
        name_ = name;
    }
    std::string getNmae() {
        return name_;
    }
    ~Toy() {
        std::cout << "Toy " << name_ << " was dropped " << std::endl;
    }
private:
    std::string name_;
};
class shared_ptr_toy {
public:
    shared_ptr_toy(std::string _nameToy):toy(new Toy(_nameToy)),quantity(new int(1)){}
    shared_ptr_toy() :toy(nullptr), quantity(nullptr) {}
    shared_ptr_toy(const shared_ptr_toy& other)
    {
        this->toy = other.toy;
        this->quantity = other.quantity;
        *(other.quantity) += 1;
    }
    shared_ptr_toy& operator=(const shared_ptr_toy& other)
    {
        if (this == &other)
            return *this;
        else
        {
            if (*(this->quantity) == 1)
            {
                delete this->quantity; 
                delete this->toy;
                this->toy = other.toy;
                this->quantity = other.quantity;
                *(other.quantity) += 1;
            }
            else
            {
                *(this->quantity) -= 1;
                this->toy = other.toy;
                this->quantity = other.quantity;
                *(other.quantity) += 1;
            }
        }        
    }
    ~shared_ptr_toy() {
        if (quantity == nullptr || *quantity == 1)
        {
            delete toy;
            delete quantity;
        }
        else
            *quantity -= 1;
    }
    void reset()
    {
        if (quantity == nullptr)
            return;
        if (*quantity == 1)
        {
            delete toy;
            delete quantity;
        }
        else
            *quantity -= 1;
        toy = nullptr;
        quantity = nullptr;
        
    }
    Toy* get()const
    {
        return toy;
    }
    int use_count()const
    {
        if (quantity == nullptr)
            return 0;
        return *quantity;
    }
    std::string getToyName()
    {
        if (toy == nullptr)
            return "Nothing";
        return toy->getNmae();
    }    
private:
    Toy* toy;
    int* quantity;    
};
shared_ptr_toy make_shared_toy(std::string _nameToy)
{
    return shared_ptr_toy(_nameToy);
}
int main() {
    shared_ptr_toy toy_01 = make_shared_toy("ball");
    shared_ptr_toy toy_02(toy_01);
    shared_ptr_toy toy_03("duck");
    std::cout << "=================================================" << std::endl;
    std::cout << toy_01.getToyName() << " links:" << toy_01.use_count() << "  "
        << toy_02.getToyName() << " links:" << toy_02.use_count() << "  "
        << toy_03.getToyName() << " links:" << toy_03.use_count() << std::endl;
    std::cout << "=================================================" << std::endl;
    toy_02 = toy_03;
    std::cout << toy_01.getToyName() << " links:" << toy_01.use_count() << "  "
        << toy_02.getToyName() << " links:" << toy_02.use_count() << "  "
        << toy_03.getToyName() << " links:" << toy_03.use_count() << std::endl;
    std::cout << "=================================================" << std::endl;
    toy_01.reset();
    std::cout << toy_01.getToyName() << " links:" << toy_01.use_count() << "  "
        << toy_02.getToyName() << " links:" << toy_02.use_count() << "  "
        << toy_03.getToyName() << " links:" << toy_03.use_count() << std::endl;
    std::cout << "=================================================" << std::endl;
    return 0;
}
