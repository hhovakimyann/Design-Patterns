#include <iostream>


struct IAnimal {
    virtual ~IAnimal() = 0;
    virtual void MakeSound() const = 0;
};
IAnimal::~IAnimal() {}

struct Dog : public IAnimal {
    void MakeSound() const {
        std::cout << "Haf-Haf" << std::endl;
    }
};

struct Cat : public IAnimal {
    void MakeSound() const {
        std::cout << "Meow~" << std::endl;
    }
};
struct Cow : public IAnimal {
    void MakeSound() const {
        std::cout << "Moo!" << std::endl;
    }
};


struct IFactory {
    virtual ~IFactory() = 0;
    virtual IAnimal* makeAnimal() const = 0;
};

IFactory::~IFactory() {}

struct DogFactory : public IFactory {
    IAnimal* makeAnimal() const {
        return new Dog();
    }
};

struct CatFactory : public IFactory {
    IAnimal* makeAnimal() const {
        return new Cat();
    }
};

struct CowFactory : public IFactory {
     IAnimal* makeAnimal() const {
        return new Cow();
    }
};

void ClientCode(const IFactory& fac) {
    auto ptr = fac.makeAnimal();
    ptr->MakeSound();
    delete ptr;
}

int main () {
    IFactory *dog = new DogFactory();
    IFactory *cat = new CatFactory();
    IFactory *cow = new CowFactory();

    ClientCode(*dog);
    ClientCode(*cat);
    ClientCode(*cow);

    delete dog;
    delete cat;
    delete cow;
}