#include <iostream>
#include <map>
#include <memory>
#include <functional>

struct IAnimal {
    virtual ~IAnimal() = default;
    virtual void MakeSound() const = 0;
};

struct Dog : public IAnimal {
    void MakeSound() const override {
        std::cout << "Haf-Haf" << std::endl;
    }
};

struct Cat : public IAnimal {
    void MakeSound() const override {
        std::cout << "Meow~" << std::endl;
    }
};

struct Cow : public IAnimal {
    void MakeSound() const override {
        std::cout << "Moo!" << std::endl;
    }
};

using AnimalFactory = std::function<std::unique_ptr<IAnimal>()>;

class AnimalRegistry {
public:
    static AnimalRegistry& Instance() {
        static AnimalRegistry instance;
        return instance;
    }

    void RegisterAnimal(const std::string& type, AnimalFactory factory) {
        factoryMap[type] = factory;
    }

    std::unique_ptr<IAnimal> CreateAnimal(const std::string& type) const {
        auto it = factoryMap.find(type);
        if (it != factoryMap.end()) {
            return it->second();
        }
        return nullptr;
    }

private:
    std::map<std::string, AnimalFactory> factoryMap;
    AnimalRegistry() = default;
};

void ClientCode(const std::string& type) {
    auto animal = AnimalRegistry::Instance().CreateAnimal(type);
    if (animal) {
        animal->MakeSound();
    } else {
        std::cout << "Unknown animal type: " << type << std::endl;
    }
}

int main() {
    AnimalRegistry::Instance().RegisterAnimal("Dog", [] { return std::make_unique<Dog>(); });
    AnimalRegistry::Instance().RegisterAnimal("Cat", [] { return std::make_unique<Cat>(); });
    AnimalRegistry::Instance().RegisterAnimal("Cow", [] { return std::make_unique<Cow>(); });

    ClientCode("Dog");
    ClientCode("Cat");
    ClientCode("Cow");
    ClientCode("Elephant"); 

    return 0;
}
