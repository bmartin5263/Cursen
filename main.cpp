#include "CursenApplication.h"
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

    CursenApplication::Run(new LobbyForm());
}