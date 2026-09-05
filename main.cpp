#include <iostream>

using namespace std;

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

void print_narrator(const char *inp_text){
    cout << "** " << inp_text << endl;
}

void print_stranger(const char *inp_text){
    cout << TermForm::cyan << "Stranger: " << inp_text << TermForm::reset << endl;
}

int main()
{
    print_narrator("It's raining outside.");
    print_narrator("You can hear a thunder strucking in the distant.");
    print_narrator("The horses seem to go even slower than before. Until they stop");
    print_narrator("Your horseman is talking to a stranger outside.");
    print_narrator("Both of them approach you");

    print_stranger("Good Evening.");
    print_stranger("We were expecting Mr. Cortes. Who are you?");

    print_narrator("You notice your horseman has surrounded and gripped you from behind.");
    print_narrator("You are stabbed by the stranger.");

    print_narrator("You died.");
}
