#pragma once
#include "Scene.h"

namespace Engine
{
	class SceneLoader
	{
	public:
		SceneLoader(Scene& scene);
		~SceneLoader() = default;

	private:
		Scene& m_scene;
	};
};
