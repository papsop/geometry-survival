#include "EditorManager.h"
#include "../Application.h"

namespace Engine
{

	EditorManager& EditorManager::Get()
	{
		return Application::Instance().GetEditorManager();
	}

}