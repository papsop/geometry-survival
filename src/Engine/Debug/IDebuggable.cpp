#include "IDebuggable.h"
#include "../Application.h"

namespace Engine
{
	void IDebuggable::OnInit()
	{
        ViewManager::Get().RegisterComponent(this);
	}

	void IDebuggable::OnDestroy()
	{
		ViewManager::Get().UnregisterComponent(this);
	}

};