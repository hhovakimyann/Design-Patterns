#include <iostream>
#include <vector>
#include <string>

class Memento {
private:
    std::string state_;
public:
    Memento(const std::string &state) : state_(state) {}
    std::string getState() const {
        return state_;
    }
};


class Creator {
private:
    std::string state_;
public:
    Memento saveState() {
        return Memento(state_);
    }

    std::string getState() const {
        return state_;
    }

    void setState(const std::string &state) {
        state_ = state;
    }

    void restoreStateFromMemento(const Memento& memento) {
        state_ = memento.getState();
        std::cout << "State restored to: " << state_ << std::endl;
    }
};


class Saver {
private:
    std::vector<Memento> vec;
public:
    void saveMemento(const Memento& obj) {
        vec.push_back(obj);
    }

    Memento getMemento(int index) {
        if(index < 0 || index > vec.size()) {
            throw std::out_of_range("Out Of Range");
        }
        return vec[index];
    }
};

int main () {
    Saver saver;
    Creator create;

    create.setState("State 1");
    saver.saveMemento(create.saveState());

    create.setState("State 2");
    saver.saveMemento(create.saveState());

    create.setState("State 3");
    saver.saveMemento(create.saveState());

    std::cout << "Current State: " << create.getState() << std::endl;

    create.restoreStateFromMemento(saver.getMemento(0));
    create.restoreStateFromMemento(saver.getMemento(1));
    create.restoreStateFromMemento(saver.getMemento(2));

}