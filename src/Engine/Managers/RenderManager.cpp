#include "RenderManager.h"
#include "../Application.h"

namespace Engine
{

	RenderManager& RenderManager::Get()
	{
		return Application::Instance().GetRenderManager();
	}

	void RenderManager::VirtualOnInit()
	{
		IEventListener<event::E_OnShowDebugKeyAction>::RegisterListener();
	}

	void RenderManager::VirtualOnDestroy()
	{
		IEventListener<event::E_OnShowDebugKeyAction>::UnregisterListener();
	}

	void RenderManager::Update(float dt)
	{
		
	}



}