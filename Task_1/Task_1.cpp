#include <iostream>
class Toy {
public:
    Toy(const std::string& name) {
        name_ = name;
    }
    std::string getName() {
        return name_;
    }
    ~Toy() {
        std::cout << "Toy " << name_ << " was dropped " << std::endl;
    }
private:
    std::string name_;
};
class Dog {
private:
    std::string name;
    std::shared_ptr<Toy> haveToy;
public:
    Dog(std::string _name, std::shared_ptr<Toy>_toy) :name(_name),haveToy(_toy){}
    Dog(std::string _name) :name(_name) { haveToy = nullptr; }
    void getToy(std::shared_ptr<Toy>_toy)
    {
        if (this->haveToy == nullptr)
        {
            std::cout << "I get toy" << std::endl;
            this->haveToy = _toy;
        }
        else if (_toy.use_count() >2)
        {
            std::cout << "Another dog is playing with this toy" << std::endl;
        }
        else if(_toy.use_count() == 2)
        {
            std::cout << "I already have this toy." << std::endl;
        }
    }
};
int main()
{
    std::shared_ptr<Toy> t1 = std::make_shared<Toy>("Stick");
    std::shared_ptr<Toy> t2 = std::make_shared<Toy>("Ball");
    std::shared_ptr<Toy> t3 = std::make_shared<Toy>("Slipper");
    Dog* dog = new Dog("Sharick");
    Dog* anotherDog = new Dog("Bonia", t2);
    dog->getToy(t1);
    dog->getToy(t2);
    dog->getToy(t3);
}
