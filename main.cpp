#include <iostream>
#include <limits>
#include <chrono>
#include <thread>

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
    
    
    constexpr const char* bg_black = "\033[40m";
    constexpr const char* bg_cyan = "\033[46m";
    constexpr const char* bg_white = "\033[47m";
}

class TextManager{
    public:
        TextManager(int& text_speed){
            _char_delay = 1000 / text_speed;
            // std::cout << _char_delay << std::endl;
        }

        void print_text(const std::string& text)
        {
            for(char ch: text) // ch = character
            {
                std::cout << ch << std::flush;
                std::this_thread::sleep_for(std::chrono::milliseconds(_char_delay));
            }
            std::cout << TermForm::reset;
            std::cout << std::endl;
        }

    private:
        int _char_delay; // in milliseconds
};

class Character
{
    public:
        Character(TextManager& textManager,
        const char* font_color,
        const char* bg_color,
        std::string prefix) :
        _textManager(textManager),
        _font_color(font_color),
        _bg_color(bg_color),
        _prefix(prefix)
        {

        }

        void say(const std::string& text)
        {
            std::cout << _font_color;
            std::cout << _bg_color;
            _textManager.print_text(_prefix+text);
        }
    
    private:

    protected:
        TextManager& _textManager;
        const char* _font_color;
        const char* _bg_color;
        std::string _prefix;
};

class Narrator : public Character
{
    public:
        Narrator(TextManager& textManager,
        const char* font_color = "",
        const char* bg_color = "",
        std::string prefix = ""):
        Character(textManager, font_color, bg_color, prefix)
        {

        }

        void say(const std::string& text)
        {
            this->_textManager.print_text(text);
        }
};

class Stranger : public Character
{
    public:
        Stranger(TextManager& textManager,
        const char* font_color = "",
        const char* bg_color = "",
        std::string prefix = ""):
        Character(textManager, font_color, bg_color, prefix)
        {

        }
};

class System : public Character
{
    public:
        System(TextManager& textManager,
        const char* font_color = "",
        const char* bg_color = "",
        std::string prefix = ""):
        Character(textManager, font_color, bg_color, prefix)
        {

        }
};

class InputManager
{
    public:
        InputManager(System& system) : _system(system){

        }

        std::string readRawData(){
            std::string rawInput;
            std::cin >> rawInput;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return rawInput;
        }

        char w82proceed(){
            _system.say("press 'Enter' to proceed");
            std::cin.get();
            return 'n';
        }

    private:
        System& _system;

};

std::string player_lastName;
std::string player_firstName;

int text_speed = 50; // in characters per second

int main()
{
    TextManager textManager = TextManager(text_speed);
    textManager.print_text("The game has started");

    Narrator narrator = Narrator(textManager);
    Stranger stranger = Stranger(textManager, TermForm::cyan, "", "[Stranger]");
    System system = System(textManager, TermForm::white, TermForm::bg_cyan);

    system.say("The game has started");

    InputManager inp = InputManager(system);

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
