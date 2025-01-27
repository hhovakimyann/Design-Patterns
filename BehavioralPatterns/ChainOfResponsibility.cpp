#include <iostream>
#include <memory>

class Handler {
public:
    virtual ~Handler() = default;
    virtual void handleRequest(int option) = 0;
};

class BillingHandler : public Handler {
public:
    void handleRequest(int option) override {
        if (option == 1) {
            std::cout << "You are being transferred to Billing support.\n";
        } else {
            std::cout << "Passing request to next handler...\n";
            nextHandler->handleRequest(option);
        }
    }
    void setNext(std::shared_ptr<Handler> handler) {
        nextHandler = handler;
    }
private:
    std::shared_ptr<Handler> nextHandler;
};

class TechSupportHandler : public Handler {
public:
    void handleRequest(int option) override {
        if (option == 2) {
            std::cout << "You are being transferred to Technical Support.\n";
        } else {
            std::cout << "Passing request to next handler...\n";
            nextHandler->handleRequest(option);
        }
    }
    void setNext(std::shared_ptr<Handler> handler) {
        nextHandler = handler;
    }
private:
    std::shared_ptr<Handler> nextHandler;
};

class FeedbackHandler : public Handler {
public:
    void handleRequest(int option) override {
        if (option == 3) {
            std::cout << "You are being transferred to Customer Feedback.\n";
        } else {
            std::cout << "Invalid option. Please try again.\n";
        }
    }
private:
    std::shared_ptr<Handler> nextHandler;
};

int main() {
    auto billing = std::make_shared<BillingHandler>();
    auto techSupport = std::make_shared<TechSupportHandler>();
    auto feedback = std::make_shared<FeedbackHandler>();

    billing->setNext(techSupport);
    techSupport->setNext(feedback);

    int userOption;
    std::cout << "Press 1 for Billing\nPress 2 for Technical Support\nPress 3 for Feedback\n";
    std::cin >> userOption;

    billing->handleRequest(userOption);

    return 0;
}
