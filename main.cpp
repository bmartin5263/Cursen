#include <chrono>
#include <thread>
#include <Uno/Other/LobbyEffectGenerator.h>
#include <bitset>
#include "Cursen/Drawing/CursesManager.h"
#include "Demo/TestForm.h"
#include "Cursen/CursenApplication.h"
#include "Uno/Network/NetworkManager.h"
#include "Uno/Data/DataManager.h"
#include "Uno/Forms/LobbyForm.h"
#include "Demo/SimpleForm.h"

int main(int argc, char **argv)
{
    using namespace cursen;

    //std::this_thread::sleep_for(std::chrono::seconds(5));
//    CursesManager::Initialize(Vect2(70,33));
//
//    chtype c = 'X';
//    c |= Color::ORANGE;
//    c ^= Color::ORANGE;
//    chtype c2 = 'X' | Color::BLUE;
//    chtype c3 = c2 ^ Color::BLUE;
//    chtype c4 = 'X' | Color::GREEN;
//    chtype c5 = 'X' | Color::GREEN;
//    chtype c6 = 'X' | Color::YELLOW;
//
//    chtype s1 = CursesManager::LLCORNER;
//    chtype s2 = CursesManager::LLCORNER | Color::BLUE;
//    chtype s3 = s2 ^ Color::BLUE;
//
//    std::string binary1 = std::bitset<32>(c).to_string();
//    std::string binary2 = std::bitset<32>(c2).to_string();
//    std::string binary3 = std::bitset<32>(c3).to_string();
//    std::string binary4 = std::bitset<32>(c4).to_string();
//    std::string binary5 = std::bitset<32>(c5).to_string();
//    std::string binary6 = std::bitset<32>(c6).to_string();
//
//    std::string sBinary1 = std::bitset<32>(s1).to_string();
//    std::string sBinary2 = std::bitset<32>(s2).to_string();
//    std::string sBinary3 = std::bitset<32>(s3).to_string();
//
//    addch(c);
//    addch(' ');
//    addstr(std::to_string(c).c_str());
//    move(1,0);
//    addstr(binary1.c_str());
//
//    move(3,0);
//    addch(c2);
//    addch(' ');
//    addstr(std::to_string(c2).c_str());
//    move(4,0);
//    addstr(binary2.c_str());
//
//    move(6,0);
//    addch(c3);
//    addch(' ');
//    addstr(std::to_string(c3).c_str());
//    move(7,0);
//    addstr(binary3.c_str());
//
//    move(9,0);
//    addch(c4);
//    addch(' ');
//    addstr(std::to_string(c4).c_str());
//    move(10,0);
//    addstr(binary4.c_str());
//
//    move(12,0);
//    addch(c5);
//    addch(' ');
//    addstr(std::to_string(c5).c_str());
//    move(13,0);
//    addstr(binary5.c_str());
//
//    move(15,0);
//    addch(c6);
//    addch(' ');
//    addstr(std::to_string(c6).c_str());
//    move(16,0);
//    addstr(binary6.c_str());
//
//    move(18,0);
//    addch(s1);
//    addch(' ');
//    addstr(std::to_string(s1).c_str());
//    move(19,0);
//    addstr(sBinary1.c_str());
//
//    move(21,0);
//    addch(s2);
//    addch(' ');
//    addstr(std::to_string(s2).c_str());
//    move(22,0);
//    addstr(sBinary2.c_str());
//
//    move(24,0);
//    addch(s3);
//    addch(' ');
//    addstr(std::to_string(s3).c_str());
//    move(25,0);
//    addstr(sBinary3.c_str());
//
//    refresh();
//    while (getch() != 'X');
//
//    CursesManager::Terminate();


    //We have networking for this program
    CursenApplication::OnUpdate([]() {
        //NetworkManager::ProcessNetworkMessages();
        DataManager::ProcessDataMessages();
    });

    CursenApplication::SetCommandLineArgs(argc, argv);

    //std::this_thread::sleep_for(std::chrono::seconds(7));
    CursenApplication::Run(new LobbyForm());

}