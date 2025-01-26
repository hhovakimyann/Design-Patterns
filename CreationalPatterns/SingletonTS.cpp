#include <iostream>
#include <mutex>

class Singleton {
private:
    static Singleton *ptr;
    static std::mutex mtx;
    Singleton() {}
    Singleton(const Singleton& obj) = delete;
    Singleton& operator=(Singleton & obj) = delete;
public:
    static Singleton* makeInstance() {
        if(ptr == nullptr) {
            std::lock_guard<std::mutex> lock(mtx);
            if(ptr == nullptr) {
                ptr = new Singleton();
            }
        }
        return ptr;
    }
};

Singleton* Singleton::ptr = nullptr;
std::mutex Singleton::mtx;
    
int main () {
    Singleton* s1 = Singleton::makeInstance();
    Singleton* s2 = Singleton::makeInstance();
    if (s1 == s2) {
        std::cout << "Both are the same instance.\n";
    }
}