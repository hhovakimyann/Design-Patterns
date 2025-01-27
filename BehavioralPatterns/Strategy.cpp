#include <iostream>
#include <vector>
#include <memory>
#include <string>

class Payment {
public:
    virtual ~Payment() = default;
    virtual void pay(int) const = 0;
};

class CreditCart : public Payment {
private:
    std::string cardNumber_;
public:
    CreditCart(const std::string cartNumber) : cardNumber_(cartNumber) {}
    void pay(int amount) const override {
        std::cout << "The User with Credit Card number " << cardNumber_ << "will pay " << amount << std::endl; 
    }
};  

class PayPal : public Payment {
private:
    std::string emailAddress_;
public:
    PayPal(const std::string &emailAddress) : emailAddress_(emailAddress) {}
    void pay(int amount) const override {
        std::cout << "The User with PayPall address " << emailAddress_  << " will pay " << amount << std::endl; 
    }
};

class Crypto : public Payment {
private:
    std::string walletAddress_;
public:
    Crypto(const std::string &walletAddress) : walletAddress_(walletAddress) {}
    void pay(int amount) const override {
        std::cout << "The User with Crypto Wallet address " << walletAddress_ << " will pay " << amount << std::endl; 
    }
};


class Strategy {
private:
    std::shared_ptr<Payment> payment;
public:
    void setStrategy(const std::shared_ptr<Payment>& set) {
        payment = set;
    }

    void payStrategy(int amount) const {
        if(payment) {
            payment->pay(amount);
        }else {
            std::cout << "Set Payment Strategy" << std::endl;
        }
    }
};

int main () {
    Strategy strategy;

    auto card = std::make_shared<CreditCart>("1234-5678-9012-3456");
    auto paypal = std::make_shared<PayPal>("example@gmail.com");
    auto crypto = std::make_shared<Crypto>("ABCDEFGH1234");


    strategy.setStrategy(card);
    strategy.payStrategy(100);

    strategy.setStrategy(paypal);
    strategy.payStrategy(200);

    strategy.setStrategy(crypto);
    strategy.payStrategy(400);
   
}