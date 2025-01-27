#include <iostream>
#include <memory>
#include <string>


class Beverage {
public:
    virtual ~Beverage() = 0;
    virtual double cost() const = 0;
    virtual std::string description() const = 0;
};
Beverage::~Beverage() {}

class Coffee : public Beverage {
public:
    double cost() const override {
        return 3.0;
    }
    std::string description() const {
        return "Coffee";
    }
};


class Espresso : public Beverage {
public:
    double cost() const override {
        return 2.5;
    }

    std::string description() const override {
        return "Espresso";
    }
};


class Decorator : public Beverage {
protected:
    std::shared_ptr<Beverage> beverage;
public:
    explicit Decorator(std::shared_ptr<Beverage> bev) : beverage(std::move(bev)) {}
};


class Milk : public Decorator {
public:
    explicit Milk(std::shared_ptr<Beverage> bev) : Decorator(std::move(bev)) {}
    
    std::string description() const override {
        return beverage->description() + " with Milk";
    }

    double cost() const override {
        return beverage->cost() + 1.0;
    }
};

class Sugar : public Decorator {
public:
    explicit Sugar(std::shared_ptr<Beverage> bev) : Decorator(std::move(bev)) {}

    std::string description() const override {
        return beverage->description() + " with Sugar";
    }

    double cost() const override {
        return beverage->cost() + 0.3;
    }
};


auto main () -> int {
    std::shared_ptr<Beverage> espresso = std::make_shared<Espresso>();
    std::cout << espresso->description() << " costs $" << espresso->cost() << std::endl;

    std::shared_ptr<Beverage> espressoWithMilk = std::make_shared<Milk>(espresso);
    std::cout << espressoWithMilk->description() << " costs $" << espressoWithMilk->cost() << std::endl;

    std::shared_ptr<Beverage> espressoWithMilkAndSugar = std::make_shared<Sugar>(espressoWithMilk);
    std::cout << espressoWithMilkAndSugar->description() << " costs $" << espressoWithMilkAndSugar->cost() << std::endl;

    std::shared_ptr<Beverage>coffee = std::make_shared<Coffee>();
}