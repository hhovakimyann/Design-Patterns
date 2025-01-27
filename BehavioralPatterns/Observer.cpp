#include <iostream>
#include <memory>
#include <vector>

class Subscriber {
public:
    virtual ~Subscriber() {}
    virtual void update(std::string) = 0;
    virtual std::string getIdentifier() const = 0;
};

class SMSSubscriber : public Subscriber {
private:
    std::string number_;
public:
    SMSSubscriber(std::string number) : number_(number) {}
    void update(std::string event) override{
        std::cout << "The '" << event << "' set to " << number_ << " number" << std::endl;
    }
    std::string  getIdentifier() const override {
        return number_;
    }
};

class EmailSubscriber : public Subscriber {
private:
    std::string email_;
public:
    EmailSubscriber(std::string email) : email_(email) {}
    void update(std::string event) override{
        std::cout << "The '" << event << "' send to " << email_ << " email" << std::endl;
    }
    std::string  getIdentifier() const override {
        return email_;
    }
};

class Publisher {
private:
    std::vector<std::shared_ptr<Subscriber>> subscribers;
public:
    void addSubscriber(const std::shared_ptr<Subscriber>& sub) {
        subscribers.push_back(sub);
    }

    void notifySubscriber(const std::string event) {
        for(const auto& ptr : subscribers) {
            ptr->update(event);
        }
    }

    void removeSubscriber(const std::string& identifier) {
        for (auto it = subscribers.begin(); it != subscribers.end(); ++it) {
            if ((*it)->getIdentifier() == identifier) {
                subscribers.erase(it);
                std::cout << "Subscriber with identifier '" << identifier << "' removed.\n";
                return;
            }
        }
        std::cout << "Subscriber with identifier '" << identifier << "' not found.\n";
    }
};

int main () {
    Publisher Iphone;

    auto email = std::make_shared<EmailSubscriber>("example@gmail.com");
    auto phone = std::make_shared<SMSSubscriber>("094000000");

    Iphone.addSubscriber(email);
    Iphone.addSubscriber(phone);

    Iphone.notifySubscriber("New Iphone available");
    Iphone.removeSubscriber("094000000");
    Iphone.removeSubscriber("094000000");
    Publisher laptop;

    auto email1 = std::make_shared<EmailSubscriber>("example1@gmail.com");
    auto email2 = std::make_shared<EmailSubscriber>("example2@gmail.com");
    auto email3 = std::make_shared<EmailSubscriber>("example3@gmail.com");

    laptop.addSubscriber(email1);
    laptop.addSubscriber(email2);
    laptop.addSubscriber(email3);
    laptop.removeSubscriber("example1@gmail.com");
    laptop.notifySubscriber("New Laptop available");

}