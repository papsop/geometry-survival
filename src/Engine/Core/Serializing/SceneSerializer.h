#pragma once
#include "../Scene.h"
#include <yaml-cpp/yaml.h>

namespace Engine
{
	class SceneSerializer
	{
	public:
		SceneSerializer(Scene& scene) : m_scene(scene) {};

		void Serialize(const std::string& filePath);
		void Deserialize(const std::string& filePath);

	private:
		void SerializeGameObject(YAML::Emitter& out, GameObject& obj);
		Scene& m_scene;
	};
}