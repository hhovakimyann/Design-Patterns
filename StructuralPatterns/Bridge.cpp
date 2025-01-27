#include <iostream>
#include <memory>
#include <string>

struct Color {
    virtual ~Color() = 0;
    virtual std::string colorType() const = 0;
};

Color::~Color() {}

struct Red : public Color {
    std::string colorType() const override {
        return "Red";
    }
};

struct Blue : public Color {
    std::string colorType() const override {
        return "Blue";
    }
};

struct Shape {
protected:
    std::shared_ptr<Color> color;
public:
    explicit Shape(std::shared_ptr<Color> color_) : color(std::move(color_)) {}
    virtual ~Shape() = 0;
    virtual void draw() const = 0;
};
Shape::~Shape() {}

struct Circle : public Shape {
    explicit Circle(std::shared_ptr<Color> color_) : Shape(std::move(color_)) {}
    void draw() const override {
        std::cout << "Draw Circle with " << color->colorType() << " color" << std::endl;
    }
};

struct Rectangle : public Shape {
    explicit Rectangle(std::shared_ptr<Color> color_) : Shape(std::move(color_)) {}
    void draw() const override {
        std::cout << "Draw Rectangle with " << color->colorType() << " color" << std::endl;
    }
};

int main() {
    std::shared_ptr<Color> red = std::make_shared<Red>();
    std::shared_ptr<Color> blue = std::make_shared<Blue>();

    std::unique_ptr<Shape> CircleRed = std::make_unique<Circle>(red);
    std::unique_ptr<Shape> CircleBlue = std::make_unique<Circle>(blue);

    std::unique_ptr<Shape> RectangleRed = std::make_unique<Rectangle>(red);
    std::unique_ptr<Shape> RectangleBlue = std::make_unique<Rectangle>(blue);

    CircleRed->draw();
    CircleBlue->draw();

    RectangleRed->draw();
    RectangleBlue->draw();

    return 0;
}
