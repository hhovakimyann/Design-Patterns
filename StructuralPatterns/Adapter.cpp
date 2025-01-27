#include <iostream>
#include <string>
#include <algorithm>

class Target {
 public:
  virtual ~Target() = default;

  virtual std::string Request() const {
    return "Target: The default target's behavior.\n";
  }
};

class Adaptee {
 public:
  std::string SpecificRequest() const {
    return ".eetpadA eht fo roivaheb laicepS\n";
  }
};


class Adapter : public Target {
private:
  Adaptee *adaptee_;
public:
    Adapter(Adaptee *adaptee) : adaptee_(adaptee) {}
    std::string Request() const override {
    std::string to_reverse = this->adaptee_->SpecificRequest();
    std::reverse(to_reverse.begin(), to_reverse.end());
    to_reverse += '\n';
    return "Adapter: (TRANSLATED) " + to_reverse;
  }
};


void ClientCode(const Target *target) {
  std::cout << target->Request();
}

int main() {
  Target *target = new Target;
  ClientCode(target);
  Adaptee *adaptee = new Adaptee;
  std::cout << "Adaptee: " << adaptee->SpecificRequest();
  Adapter *adapter = new Adapter(adaptee);
  ClientCode(adapter);

  delete target;
  delete adaptee;
  delete adapter;

  return 0;
}