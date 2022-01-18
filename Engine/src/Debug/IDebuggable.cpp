#include "IDebuggable.h"
#include "../Application.h"

namespace Engine
{
    IDebuggable::IDebuggable()
    {
        SubsystemManager::Get().GetViewSubsystem().RegisterComponent(this);
    }
};