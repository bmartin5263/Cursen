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
       CursesManager::DrawStringBottomLeft(std::to_string(num_updates));
    });

    CursenApplication::Run(new LobbyForm());
}