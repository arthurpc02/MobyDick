#include <iostream>
#include <limits>

namespace TermForm {
    constexpr const char* reset = "\033[0m";
    constexpr const char* black = "\033[30m";
    constexpr const char* red = "\033[31m";
    constexpr const char* green = "\033[32m";
    constexpr const char* yellow = "\033[33m";
    constexpr const char* blue = "\033[34m";
    constexpr const char* purple = "\033[35m";
    constexpr const char* cyan = "\033[36m";
    constexpr const char* white = "\033[37m";
}

class Character
{
    public:
        Character()
        {

        }

        virtual void say(const std::string& text){}
};

class Narrator : public Character
{
    public:
    void say(const std::string& text)
    {
        std::cout << text << std::endl;
    }
};

class Stranger : public Character
{
    public:
    void say(const std::string& text)
    {
        std::cout << TermForm::cyan << "[Stranger] " << text << TermForm::reset << std::endl;
    }
};

class InputManager
{
    public:
        InputManager(){}

        std::string readRawData(){
            std::string rawInput;
            std::cin >> rawInput;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return rawInput;
        }

        char w82proceed(){
            std::cin.get();
            return 'n';
        }

    private:

};

std::string player_lastName;
std::string player_firstName;

int main()
{
    Narrator narrator = Narrator();
    Stranger stranger = Stranger();

    InputManager inp = InputManager();

    narrator.say("You wake up. It's still raining. Very lightly.");
    narrator.say("The smell of seawater is already present in the air");
    narrator.say("The horses seem to go even slower than before. Until they stop");
    inp.w82proceed();
    narrator.say("...");
    narrator.say("Your coachman is talking to a stranger outside, on the front porch of what seems to be an inn.");
    narrator.say("You jump out of the carriage and join them.");

    stranger.say("Good Evening.");
    stranger.say("I need your last name.");

    player_lastName = inp.readRawData();
    
    stranger.say(player_lastName + ", right?");
    stranger.say("Now your first name:");
    
    player_firstName = inp.readRawData();
    
    stranger.say(player_firstName + " " + player_lastName + "?");
    narrator.say("He laughs loud. One time only. And then stops. The coachman is bored and wants to be paid.");
    inp.w82proceed();
    narrator.say("You notice your coachman has surrounded and gripped you from behind.");
    narrator.say("The stranger stabbed you.");

    narrator.say("You died.");
}
