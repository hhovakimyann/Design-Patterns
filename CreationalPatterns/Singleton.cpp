#include <iostream>


class Singleton {
private:
    static Singleton * sign_;
    Singleton() = default;

public:

    Singleton(const Singleton& obj) = delete;
    Singleton& operator=(const Singleton& obj) = delete;

    static Singleton* getInstance() {
        if(sign_ == nullptr) {
            sign_ = new Singleton();
        }
        return sign_;
    }
    void displayMessage() const {
        std::cout << "Singleton instance address: " << this << std::endl;
    }
};

Singleton* Singleton::sign_ = nullptr;


int main () {
    Singleton* instance1 = Singleton::getInstance();
    instance1->displayMessage();

    Singleton* instance2 = Singleton::getInstance();
    instance2->displayMessage();

    if (instance1 == instance2) {
        std::cout << "Both instances are the same, Singleton works!" << std::endl;
    } else {
        std::cout << "Instances are different, Singleton failed!" << std::endl;
    }

    return 0;
}

