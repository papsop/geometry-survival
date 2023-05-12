#include "IDebuggable.h"
#include "../Application.h"
#include "../Managers/RenderManager.h"

namespace Engine
{
	void IDebuggable::DebuggableOnInit()
	{
		RenderManager::Get().RegisterComponent(this);
	}

	void IDebuggable::DebuggableOnDestroy()
	{
    RenderManager::Get().UnregisterComponent(this);
	}

};