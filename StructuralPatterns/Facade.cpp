#include <iostream>
#include <string>

class Device {
public:
    virtual ~Device() = default;
    virtual void on() const = 0;
    virtual void off() const = 0;
};

class Projector : public Device {
public:
    void on() const override{
        std::cout << "Projector: Turning On" << std::endl;
    }

    void off() const override {
        std::cout << "Projector: Turning Off" << std::endl;
    }

    void wideScreenMode() {
        std::cout << "Projector: Setting to widescreen mode." << std::endl;
    }
};

class Amplifier : public Device{
public:
    void on() const override{
        std::cout << "Amplifier: Turning on." << std::endl;
    }
    void off() const override{
        std::cout << "Amplifier: Turning off." << std::endl;
    }
    void setVolume(int level) {
        std::cout << "Amplifier: Setting volume to " << level << "." << std::endl;
    }
};

class DVDPlayer : public Device {
public:
    void on() const override {
        std::cout << "DVD Player: Turning On" << std::endl;
    }

    void off() const override {
        std::cout << "DVD Player: Turning Off" << std::endl;
    }

    void play(const std::string& movie) {
        std::cout << "DVD Player: Playing " << movie << "." << std::endl;
    }
};

class House {
private:
    Projector* projector;
    Amplifier* amplifier;
    DVDPlayer* player;
public:
    House(Projector* ptr1, Amplifier* ptr2, DVDPlayer* ptr3) :projector(ptr1), amplifier(ptr2), player(ptr3) {}
    void watchMovie(const std::string& movie) {
        std::cout << "Preparing to watch a movie..." << std::endl;
        amplifier->on();
        amplifier->setVolume(5);
        projector->on();
        projector->wideScreenMode();
        player->on();
        player->play(movie);
        std::cout << "Movie started: Enjoy!" << std::endl;
    }

    void endMovie() const {
        std::cout << "Shutting down the home theater system..." << std::endl;
        player->off();
        projector->off();
        amplifier->off();
        std::cout << "Goodbye!" << std::endl;
    }
};

int main () {
    Projector *projector = new Projector();
    DVDPlayer *player = new DVDPlayer();
    Amplifier *amp = new Amplifier();

    House obj(projector,amp,player);
    obj.watchMovie("Pablo Escobar");
    obj.endMovie();
}