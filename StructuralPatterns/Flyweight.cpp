#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

class Character {
public:
    virtual ~Character() = default;
    virtual void render(int font, const std::string& color) const = 0;
};

class ConcreateCharacter : public Character {
public:
    char symbol;
public:
    ConcreateCharacter(char s) : symbol(s) {}
    void render(int font, const std::string& color) const override{
        std::cout << "The character with " << font << "and " << color << " was rendered" << std::endl;
    }
};

class CharacterFactory  {
private:
    std::unordered_map<char, std::shared_ptr<Character>> map;
public:
    std::shared_ptr<Character> getCharacter(char c) {
        if(map.find(c) == map.end()) {
            map[c]  = std::make_shared<ConcreateCharacter>(c);
            std::cout << "Creating New Character for " << c << std::endl;
        }
        return map[c];
    }

};


int main () {
    CharacterFactory factory;

    std::string text = "HELLO WORLD";
    for (char c : text) {
        if (c != ' ') { 
            auto character = factory.getCharacter(c);
            character->render(12, "blue"); 
        }
    }

    std::cout << "Reusing flyweights:" << std::endl;;
    text = "HELLO CHARACTER";
    for (char c : text) {
        if (c != ' ') {
            auto character = factory.getCharacter(c);
            character->render(16, "red");
        }
    }

    return 0;
}