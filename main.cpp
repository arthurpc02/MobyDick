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
        TextManager(){

        }

        // prints text with typewriter effect
        void print_text(const std::string& text, const char* font_color, const char* bg_color, int textSpeed)
        {
            int char_delay_ms = 1000/textSpeed;
            std::cout << font_color;
            std::cout << bg_color;
            for(char ch: text) // ch = character
            {
                std::cout << ch << std::flush;
                std::this_thread::sleep_for(std::chrono::milliseconds(char_delay_ms));
            }
            std::cout << TermForm::reset;
            std::cout << std::endl;
        }
};

class Character
{
    public:
        Character(TextManager& textManager, std::string name, bool display_name = false,
        const char* font_color = "", const char* bg_color = "", int textSpeed = 150) :
        _textManager(textManager), _name(name), _display_name(display_name), _font_color(font_color),
        _bg_color(bg_color), _textSpeed(textSpeed)
        {

        }

        void say(std::string text)
        {
            if(_display_name)
            {
                text = "[" + _name + "]" + text;
            }

            _textManager.print_text(text, _font_color, _bg_color, _textSpeed);
        }
    
    private:
        TextManager& _textManager;
        std::string _name;
        bool _display_name;
        const char* _font_color;
        const char* _bg_color;
        int _textSpeed; // characters per second
};

class InputManager
{
    public:
        InputManager(Character& input_hint) : _input_hint(input_hint){

        }

        std::string readRawData(){
            std::string rawInput;
            std::cin >> rawInput;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return rawInput;
        }

        char w82proceed(){
            _input_hint.say("press 'Enter' to proceed");
            std::cin.get();
            return 'n';
        }

    private:
        Character& _input_hint;

};

std::string player_lastName;
std::string player_firstName;
std::string name_ship;

int main()
{
    TextManager textManager = TextManager();

    Character narrator = Character(textManager, "Narrator");
    Character stranger = Character(textManager, "Stranger", true, TermForm::cyan, "");
    Character input_hint = Character(textManager, "Input Hints", false, TermForm::white, TermForm::bg_cyan, 1000);

    InputManager inp = InputManager(input_hint);

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
    narrator.say("The Stranger throws a coin to the coachman and he immediatly prepares to leave.");
    
    stranger.say("I'm De La Croix. Captain Ahab and our Stakeholder put me in charge of receiving you besides other stuff.");
    Character delacroix = Character(textManager, "De La Croix", true, TermForm::cyan);
    delacroix.say("The Ship... hummm....");
    delacroix.say("...");
    delacroix.say("ermm...");
    delacroix.say("...");
    narrator.say("He whispers:");
    delacroix.say("*What was its name?*");
    
    name_ship = inp.readRawData();
    
    delacroix.say(name_ship + "! I knew it.");

    narrator.say("You died.");
}
