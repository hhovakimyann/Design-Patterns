#include <iostream>
#include <memory>
#include <vector>
#include <string>

class Context;

class State {
public:
    virtual ~State() = default;
    virtual void handle(Context & obj) = 0;
    virtual std::string getState() const = 0;
};

class GreenState : public State{
public:
    void handle(Context& obj) override;
    std::string getState() const override {
        return "Green";
    }
};


class YellowState : public State {
public:

    void handle(Context & obj) override;
    std::string getState() const override {
        return "Yellow";
    }
};

class RedState : public State {
public:
    void handle(Context &obj) override;
    std::string getState() const override {
        return "Red";
    }
};

class Context {
private:
    std::shared_ptr<State> state;
public:
    void setState(const std::shared_ptr<State> state_) {
        state = state_;
    }

    void request() {
        if(state) {
            std::cout << "Current State " << state->getState() << std::endl;
            state->handle(*this);
        }
    }
};


void RedState::handle(Context& obj) {
     std::cout << "Transitioning from Red to Greed" << std::endl;
    obj.setState(std::make_shared<GreenState>());
}



void YellowState::handle(Context& obj) {
    std::cout << "Transitioning from Yellow to Red" << std::endl;
    obj.setState(std::make_shared<YellowState>());
}


void GreenState::handle(Context& obj) {
    std::cout << "Transitioning from Green to Yellow" << std::endl;
    obj.setState(std::make_shared<YellowState>());
}



int main () {
    Context context;
    auto init = std::make_shared<GreenState>();

    context.setState(init);

    for(int i = 0; i < 10; i++) {
        context.request();
    }
}