#include <iostream>

class CoffeeMachine {
public:
    void makeCoffee() {
        boilWater();
        brew();
        pourInCup();
        addCondiments();
    }
protected:
    void boilWater() const {
        std::cout << "Boil Water" << std::endl;
    }
    virtual void brew() const = 0;
    virtual void addCondiments() const = 0;
    void pourInCup() const {
        std::cout << "Pouring into to cap" << std::endl;
    }
};

class BlackCoffee : public CoffeeMachine {
protected:
    void brew() const override {
        std::cout << "Brew black coffee" << std::endl;
    }
    void addCondiments() const override {
        std::cout << "No adding Condiments" << std::endl;
    }
};

class Espresso : public CoffeeMachine {
protected:
    void brew() const override {
        std::cout << "Brewing coffee for Es" << std::endl;
    }

    void addCondiments() const override {
        std::cout << "Added Sugar" << std::endl;
    }
};


int main () {
    std::cout << "Making Black Coffee:\n";
    BlackCoffee black;
    black.makeCoffee();

    std::cout << "Making Latte:\n";
    Espresso latte;
    latte.makeCoffee();
}