#include <iostream>
#include <string>

class IImage {
public:
    virtual void display() const = 0;
    virtual ~IImage() = default;
};

class RealImage : public IImage {
private:
    std::string image_;
     void loadFromDisk() const {
        std::cout << "Loading image from disk: " << filename << std::endl;
    }
public:
    RealImage(const std::string& str) : image_(str) {}
    void display() const override {
        std::cout << "Displaying Image " << image_ << std::endl;
    }
};
int main () {

}