#include <iostream>
#include <memory>

struct Command {
    virtual void execute() const = 0;
    virtual ~Command() = default;
};


struct Light {
    void on() const{
        std::cout << "Light On" << std::endl;
    }
    void off() const {
        std::cout << "Turn Off" << std::endl;
    }
};

struct TurnOffCommand : public Command {
private:
    Light &obj;
public:
    TurnOffCommand(Light &off) : obj(off) {}

    void execute() const override {
        obj.off();
    }
};


struct TurnOnCommand : public Command {
private:
    Light &obj;
public:
    TurnOnCommand(Light &off) : obj(off) {}

    void execute() const override {
        obj.on();
    }
};

class Control {
private:
    std::unique_ptr<Command> ptr;
public:
    void set(std::unique_ptr<Command> ptr_) {
        ptr = std::move(ptr_);
    } 
    void pressButton() {
        if (ptr) ptr->execute();
    }
};  

int main () {
    Light light;
    Control control;

    control.set(std::make_unique<TurnOffCommand>(light));
    control.pressButton();


    control.set(std::make_unique<TurnOnCommand>(light));
    control.pressButton();

}