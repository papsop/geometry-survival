#include "IDebuggable.h"
#include "../Application.h"

namespace Engine
{
	void IDebuggable::DebuggableOnInit()
	{
		ViewManager::Get().RegisterComponent(this);
	}

	void IDebuggable::DebuggableOnDestroy()
	{
		ViewManager::Get().UnregisterComponent(this);
	}

};