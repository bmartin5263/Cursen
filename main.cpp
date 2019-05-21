#include <chrono>
#include <thread>
#include "Cursen/Drawing/CursesManager.h"
#include "Demo/TestForm.h"
#include "Cursen/CursenApplication.h"
#include "Uno/Network/NetworkManager.h"
#include "Uno/Data/DataManager.h"
#include "Uno/Forms/LobbyForm.h"

int main()
{
    using namespace cursen;

    // We have networking for this program
    CursenApplication::OnUpdate([]() {
        NetworkManager::ProcessNetworkMessages();
        DataManager::ProcessDataMessages();
    });

    CursenApplication::OnDraw([]() {
       static int num_updates = 0;
       num_updates++;
       //CursesManager::DrawStringBottomLeft(std::to_string(num_updates));
    });

    //std::this_thread::sleep_for(std::chrono::seconds(7));
    CursenApplication::Run(new LobbyForm());
}