#include "IDebuggable.h"
#include "../Application.h"
#include "../Managers/ViewManager.h"
#include "../Managers/RenderManager.h"

namespace Engine
{
	void IDebuggable::DebuggableOnInit()
	{
		//ViewManager::Get().RegisterComponent(this);
		RenderManager::Get().RegisterComponent(this);
	}

	void IDebuggable::DebuggableOnDestroy()
	{
    //ViewManager::Get().UnregisterComponent(this);
    RenderManager::Get().UnregisterComponent(this);
	}

};