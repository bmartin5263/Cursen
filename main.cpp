#include <chrono>
#include <thread>
#include <Uno/Other/LobbyEffectGenerator.h>
#include <bitset>
#include <Uno/Serverus/NetDevice.h>
#include <Uno/Serverus/Serverus.h>
#include <Simon/SimonForm.h>
#include <Tetris/Forms/GameForm.h>
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

    //We have networking for this program
    CursenApplication::OnUpdate([]()
    {
        NetworkManager::ProcessNetworkMessages();
        DataManager::ProcessDataMessages();
    });

    //std::this_thread::sleep_for(std::chrono::seconds(7));
    Form* lobbyForm = new LobbyForm;
    //LobbyForm lobbyForm1;
    CursenApplication::Run(lobbyForm);

}