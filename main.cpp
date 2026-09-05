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



int main()
{
    std::cout << TermForm::red << "Red text" << TermForm::reset << "\n";
//           ^red code^                ^reset^
    cout << "** Está chovendo lá fora."<< endl;
    cout<<"** You can hear thunder strucking in the distant."<<endl;
    cout<<"** The horses seem to go even slower than before."<<endl;
    cout<<"** The horses seem to go even slower than before."<<endl;

    cout<< TermForm::cyan << "Stranger: Good Evening."<< TermForm::reset <<endl;
    cout<<"Stranger: We were expecting Mr. Cortes. Who are you?"<<endl;



    cout<<"\n** Good-bye Cruel World!"<<endl;
}
