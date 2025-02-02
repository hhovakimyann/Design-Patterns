#include <iostream>
#include <vector>

class Restaurant;
class Factory;

class TaxAuditor {
public:
    virtual ~TaxAuditor() = default;
    virtual void restaurant(Restaurant *) const = 0;
    virtual void factory(Factory *) const = 0;
};

class Business {
public:
    virtual ~Business() = default;
    virtual void accept(TaxAuditor *) = 0;
};

class Restaurant : public Business{
public:
    void accept(TaxAuditor *obj) {
        obj->restaurant(this);
    }
};



class Factory : public Business{
public:
    void accept(TaxAuditor *obj) {
        obj->factory(this);
    }
};

class ConcreateTax : public TaxAuditor {
public:
    void restaurant(Restaurant * obj) const {
        std::cout << "Auditing Restaurant: Applying food industry tax rules." << std::endl;
    }


    void factory(Factory * obj) const {
        std::cout << "Auditing Factory: Applying manufacturing industry tax rules." << std::endl;
    }
};

int main () {
    std::vector<Business*> businesses = {new Restaurant(), new Factory()};

    ConcreateTax auditor;

    for (Business* business : businesses) {
        business->accept(&auditor);
    }

    for (Business* business : businesses) {
        delete business;
    }

    return 0;
}