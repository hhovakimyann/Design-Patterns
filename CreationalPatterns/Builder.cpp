#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Computer {
private:
   string cpu;
   string gpu;
   string ram;
   string storage;
   string powerSupply;


public:
   void setCPU(const string& cpu) { this->cpu = cpu; }
   void setGPU(const string& gpu) { this->gpu = gpu; }
   void setRAM(const string& ram) { this->ram = ram; }
   void setStorage(const string& storage) { this->storage = storage; }
   void setPowerSupply(const string& powerSupply) { this->powerSupply = powerSupply; }


   void showSpecs() const {
       cout << "CPU: " << cpu << "\n";
       cout << "GPU: " << gpu << "\n";
       cout << "RAM: " << ram << "\n";
       cout << "Storage: " << storage << "\n";
       cout << "Power Supply: " << powerSupply << "\n";
   }
};




class ComputerBuilder {
public:
   virtual ~ComputerBuilder() {}
   virtual void buildCPU() = 0;
   virtual void buildGPU() = 0;
   virtual void buildRAM() = 0;
   virtual void buildStorage() = 0;
   virtual void buildPowerSupply() = 0;
   virtual Computer* getComputer() = 0;
};




class GamingComputerBuilder : public ComputerBuilder {
private:
   Computer* computer;


public:
   GamingComputerBuilder() : computer(new Computer()) {}
   void buildCPU() override { computer->setCPU("Intel Core i9"); }
   void buildGPU() override { computer->setGPU("NVIDIA RTX 4090"); }
   void buildRAM() override { computer->setRAM("32GB DDR5"); }
   void buildStorage() override { computer->setStorage("2TB NVMe SSD"); }
   void buildPowerSupply() override { computer->setPowerSupply("850W Gold"); }


   Computer* getComputer() override { return computer; }
};




class OfficeComputerBuilder : public ComputerBuilder {
private:
   Computer* computer;


public:
   OfficeComputerBuilder() : computer(new Computer()) {}


   void buildCPU() override { computer->setCPU("Intel Core i5"); }
   void buildGPU() override { computer->setGPU("Integrated Graphics"); }
   void buildRAM() override { computer->setRAM("16GB DDR4"); }
   void buildStorage() override { computer->setStorage("512GB SSD"); }
   void buildPowerSupply() override { computer->setPowerSupply("500W Bronze"); }


   Computer* getComputer() override { return computer; }
};




class ComputerDirector {
private:
   ComputerBuilder* builder;


public:
   void setBuilder(ComputerBuilder* builder) {
       this->builder = builder;
   }


   Computer* constructComputer() {
       builder->buildCPU();
       builder->buildGPU();
       builder->buildRAM();
       builder->buildStorage();
       builder->buildPowerSupply();
       return builder->getComputer();
   }
};




int main() {
   ComputerDirector director;


   GamingComputerBuilder gamingBuilder;
   director.setBuilder(&gamingBuilder);
   Computer* gamingComputer = director.constructComputer();
   cout << "Gaming Computer:\n";
   gamingComputer->showSpecs();
   delete gamingComputer; 


   OfficeComputerBuilder officeBuilder;
   director.setBuilder(&officeBuilder);
   Computer* officeComputer = director.constructComputer();
   cout << "\nOffice Computer:\n";
   officeComputer->showSpecs();
   delete officeComputer;
}
