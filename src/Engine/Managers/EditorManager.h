#pragma once
#include "IManager.h"

namespace Engine
{
	// config manager
	class EditorManager : public IManager
	{
	public:

		static EditorManager& Get();
		~EditorManager() = default;

	private:
		EditorManager() = default;

		friend class Application;
	};

};