#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Colleague {
public:
    virtual ~Colleague() = default;
    virtual std::string getName() const = 0;
    virtual void send(const std::string& message, const std::string& sender) const = 0;
};
class Mediator {
public:
    virtual ~Mediator() = default;
    virtual void sendMessage(const std::string& name_, const std::string& message) const = 0;
    virtual void addGroup(const std::shared_ptr<Colleague>& user_) = 0;
};

class User : public Colleague {
private:
    Mediator * ptr_;
    std::string name_;
public:
    User(std::string name, Mediator* ptr = nullptr) : name_(name), ptr_(ptr) {}
    std::string getName() const override {
        return name_;
    }
    void sendMessage(const std::string& message) const {
        std::cout << name_ << " sends: " << message << std::endl;
        ptr_->sendMessage(name_,message);
    }
    void send(const std::string& message, const std::string &sender) const override {
        std::cout << name_ << " receives from " << sender << ": " << message << std::endl;
    }
};



class ChatGroup : public Mediator  {
private:
    std::vector<std::shared_ptr<Colleague>> users;
public:
    void addGroup(const std::shared_ptr<Colleague> & user_)  {
        users.push_back(user_);
    }
    void sendMessage(const std::string& name_, const std::string& message_) const {
        for(const auto& ptr : users) {
            if(ptr->getName() != name_) {
                ptr->send(message_,name_);
            }
        }
    }
};

int main () {
    ChatGroup chatRoom;

    auto alice = std::make_shared<User>("Alice", &chatRoom);
    auto bob = std::make_shared<User>("Bob", &chatRoom);
    auto charlie = std::make_shared<User>("Charlie", &chatRoom);

    chatRoom.addGroup(alice);
    chatRoom.addGroup(bob);
    chatRoom.addGroup(charlie);

    alice->sendMessage("Hello everyone!");
    bob->sendMessage("Hi Alice!");
    charlie->sendMessage("Good morning!");

}