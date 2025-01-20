#include <iostream>



struct Chair {
    virtual ~Chair() {}
    virtual void seatOn() const = 0;
};

struct ModernChair : public Chair{
    void seatOn() const {
        std::cout << "Seat On Modern Chair" << std::endl;
    }
};

struct VictorianChair : public Chair{
    void seatOn() const {
        std::cout << "Seat On Victorian Chair" << std::endl;
    }
};


struct Table {
    virtual ~Table() {}
    virtual void eatOn() const = 0;
};

struct ModernTable : public Table{
    void eatOn() const {
        std::cout << "Eat On Modern Table" << std::endl;
    }
};

struct VictorianTable : public Table{
    void eatOn() const {
        std::cout << "Eat On Victorian Table" << std::endl;
    }
};

struct CoffeeTable {
    virtual ~CoffeeTable() {}
    virtual void drink() const = 0;
};

struct ModernCoffeeTable : public CoffeeTable{
    void drink() const {
        std::cout << "Drink Modern CoffeeTable" << std::endl;
    }
};

struct VictorianCoffeeTable : public CoffeeTable{
    void drink() const {
        std::cout << "Drink Victorian Table" << std::endl;
    }
};


struct IFactory {
    virtual ~IFactory() = 0;
    virtual Chair *makeChair() const = 0;
    virtual Table* makeTable() const = 0;
    virtual CoffeeTable * makeCoffeeTable() const = 0;
};
IFactory::~IFactory() {}

struct ModernFactory : public IFactory{
    Chair* makeChair() const {
        return new ModernChair();
    }
    Table* makeTable() const {
        return new ModernTable();
    }
    CoffeeTable* makeCoffeeTable() const {
        return new ModernCoffeeTable();
    }
};

struct VictorianFactory : public IFactory{
    Chair* makeChair() const {
        return new VictorianChair();
    }
    Table* makeTable() const {
        return new VictorianTable();
    }
    CoffeeTable* makeCoffeeTable() const {
        return new VictorianCoffeeTable();
    }
};



void ClientCode(const IFactory& fac) {

    auto chair = fac.makeChair();
    chair->seatOn();

    auto table = fac.makeTable();
    table->eatOn();

    auto coffeeTable = fac.makeCoffeeTable();
    coffeeTable->drink();
    std::cout << std::endl;
    delete chair;
    delete table;
    delete coffeeTable; 
}


int main () {
    IFactory * modern = new ModernFactory();
    IFactory * victorian = new VictorianFactory();

    ClientCode(*modern);
    ClientCode(*victorian);

    delete modern;
    delete victorian;
}