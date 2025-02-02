#include <iostream>
#include <vector>
#include <string>

template <typename T>
class Iterator {
public:
    virtual bool hasNext() = 0;
    virtual T getNext() = 0;
    virtual ~Iterator() = default;  
};

template <typename T>
class IterableCollection {
public:
    virtual Iterator<T>* createIterator() = 0;
    virtual ~IterableCollection() = default;  
};

template <typename T>
class TVChannelIterator : public Iterator<T> {
private:
    int index = 0;
    std::vector<T> vec;
public:
    TVChannelIterator(std::vector<T> ch) : vec(ch) {} 

    bool hasNext() override {
        return index < vec.size();
    }

    T getNext() override {
        return vec[index++];
    }
};

class TVChannelCollection : public IterableCollection<std::string> {
private:
    std::vector<std::string> channels;

public:
    void addChannel(const std::string& channel) {
        channels.push_back(channel);
    }

    Iterator<std::string>* createIterator() override {
        return new TVChannelIterator<std::string>(channels);  
    }
};

int main() {
    TVChannelCollection tvChannels;
    tvChannels.addChannel("HBO");
    tvChannels.addChannel("Netflix");
    tvChannels.addChannel("ESPN");
    tvChannels.addChannel("National Geographic");

    Iterator<std::string>* iterator = tvChannels.createIterator();

    std::cout << "TV Channel List:\n";
    while (iterator->hasNext()) {
        std::cout << "- " << iterator->getNext() << std::endl;
    }

    delete iterator;
    return 0;
}
