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

// TODO Run should work with stack-allocated forms
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
    LobbyForm* lobbyForm = new LobbyForm;
    CursenApplication::Run(lobbyForm);

}