#include <iostream>

class Prototype {
public:
    virtual Prototype * cloneMethod() const = 0;
    virtual ~Prototype() {};
    virtual void print() const = 0;
};


class Circle : public Prototype{
private:
    int radius;
    std::string color;
public:
    Circle(int radius_, const std::string& color_) : radius(radius_), color(color_) {}
    void print() const override {
        std::cout << "Radius " << radius << " Color " << color << std::endl;
    }
    Prototype * cloneMethod() const{
        return new Circle(*this);
    }
};


class Rectangle : public Prototype{
private:
    int wight;
    int height;
    std::string color;
public:
    Rectangle(int wight_, int height_, const std::string& color_) : wight(wight_), height(height_), color(color_) {}
    void print() const override {
        std::cout << "Wight " << wight << " Height " << height << " Color " << color << std::endl;
    }
    Prototype * cloneMethod() const{
        return new Rectangle(*this);
    }
};

int main () {
    Circle originalCircle(10, "Red");
    Rectangle originalRectangle(5, 8, "Blue");

    Prototype* clonedCircle = originalCircle.cloneMethod();
    Prototype* clonedRectangle = originalRectangle.cloneMethod();

    clonedCircle->print();
    clonedRectangle->print();

    delete clonedCircle;
    delete clonedRectangle;
}