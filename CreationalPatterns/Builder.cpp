#include <iostream>
#include <string>

class ProductCar {
private:
    std::string color;
    std::string name;
    std::string engine;
public:
    std::string getColor() {
        return color;
    }
    void setColor(const std::string color_) {
        color = color_;
    }

    std::string getName() {
        return name;
    }
    void setName(const std::string name_) {
        name = name_;
    }

    std::string getEngine() {
        return engine;
    }
    
    void setEngine(const std::string engine_) {
        engine = engine_;
    }

    void showDetails() const {
        std::cout << "Car Name: " << name << ", Engine: " << engine << ", Color: " << color << std::endl;
    }
};


class CarBuilder {
protected:
    ProductCar *car;
public:
    CarBuilder() : car(new ProductCar()) {}
    virtual ~CarBuilder() {
        delete car;
    }

    ProductCar* getCar() const {
        return car;
    }

    virtual void buildName() const = 0;
    virtual void buildEngine() const = 0;
    virtual void buildColor() const = 0;
};


class DefaultCar : public CarBuilder {
public:
    void buildName() const override {
        car->setName("Opel");
    }

    void buildColor() const override {
        car->setColor("Red");
    }
    
    void buildEngine() const override {
        car->setEngine("1.6 Eco");
    }
};

class SportCar : public CarBuilder {
public:
    void buildName() const override {
        car->setName("Porsche");
    }

    void buildColor() const override {
        car->setColor("White and Black");
    }
    
    void buildEngine() const override {
        car->setEngine("6.3");
    }
};

class Director {
private:
    CarBuilder* builder;
public: 
    void setBuilder(CarBuilder* car) {
        builder = car;
    }

    void carConstruct() const {
        builder->buildColor();
        builder->buildEngine();
        builder->buildName();
    }

    ProductCar* getCar() const {
        return builder->getCar();
    }
};

int main () {
    Director director;
    
    DefaultCar* defCar = new DefaultCar();
    director.setBuilder(defCar);
    director.carConstruct();

    ProductCar* car1 = director.getCar();
    car1->showDetails();
   
    SportCar* sportCar = new SportCar();
    director.setBuilder(sportCar);
    director.carConstruct();

    ProductCar* car2 = director.getCar();
    car2->showDetails();

    delete defCar;
    delete sportCar;

    return 0;
}
