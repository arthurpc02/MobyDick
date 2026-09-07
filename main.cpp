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
                text = "[" + _name + "] " + text;
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
        
        int ReadOptions(const std::string& opt1 = "", const std::string& opt2 = "", const std::string& opt3 = "", const std::string& opt4 = "", const std::string& opt5 = "", const std::string& opt6 = "")
        {
            _input_hint.say("1. " + opt1);
            _input_hint.say("2. " + opt2);
            _input_hint.say("3. " + opt3);
            _input_hint.say("4. " + opt4);
            _input_hint.say("5. " + opt5);
            _input_hint.say("6. " + opt6);

            int rawInput = 0;
            while(rawInput != 1 && rawInput != 2 && rawInput != 3&& rawInput != 4 && rawInput != 5 && rawInput != 6)
            {
                std::cin >> rawInput;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

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

class GameState
{
    public:
        std::string player_lastName;
        std::string player_firstName;
        std::string ship_name;

        GameState(Character& text) : _text(text){}


        std::string get_playerFullName()
        {
            return player_firstName + player_lastName;
        }

        int get_playerMoney()
        {
            return _player_money;
        }

        unsigned int add_playerMoney(unsigned int amount)
        {
            // todo: avoid overflows
            _player_money += amount;
            _text.say(std::to_string(amount) + "$ was added to your wallet.");
            return _player_money;
        }

        unsigned int remove_playerMoney(unsigned int amount)
        {
            // todo: avoid overflows
            // todo: avoid purchase when not enough money
            _player_money -= amount;
            _text.say(std::to_string(amount) + "$ was removed from your wallet.");
            return _player_money;
        }

    private:
        Character& _text;
        unsigned int _player_money = 100;
};

int main()
{
    TextManager textManager = TextManager();
    Character game_status = Character(textManager, "Game Status", false, TermForm::black, TermForm::bg_white);
    GameState gameState = GameState(game_status);

    Character narrator = Character(textManager, "Narrator");
    Character stranger = Character(textManager, "Stranger", true, TermForm::green, "");
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

    gameState.player_lastName = inp.readRawData();
    
    stranger.say(gameState.player_lastName + ", right?");
    stranger.say("Now your first name:");
    
    gameState.player_firstName = inp.readRawData();
    
    stranger.say(gameState.player_firstName + " " + gameState.player_lastName + "?");
    narrator.say("He laughs loud. One time only. And then stops. The coachman is bored and wants to be paid.");
    inp.w82proceed();
    narrator.say("The Stranger throws a coin to the coachman and he immediatly prepares to leave.");
    
    stranger.say("I'm De La Croix. Captain Ahab and our Stakeholders put me in charge of receiving you.");
    Character delacroix = Character(textManager, "De La Croix", true, TermForm::green);
    delacroix.say("The Ship... hummm....");
    delacroix.say("...");
    delacroix.say("ermm...");
    delacroix.say("...");
    narrator.say("He whispers:");
    delacroix.say("*What was its name?*");
    
    gameState.ship_name = inp.readRawData();
    
    delacroix.say(gameState.ship_name + "! I knew it.");
    delacroix.say(gameState.ship_name + " leaves in three days.");
    delacroix.say("Now,");
    delacroix.say("It will cost you $15 for the three days at the inn.");
    
    int ans1 = inp.ReadOptions("Really?! Take it then.", "Really?! I thought the expenses were covered?!", "Not paying.");
    if(ans1 == 1){
        gameState.remove_playerMoney(15);
    }    
    
    narrator.say("He laughs loud again. One time only. And then invites you inside.");

    narrator.say("You died.");
}
