#include "SceneSerializer.h"
#include "../GameObject/GameObject.h"
#include "../../Managers/GameObjectManager.h"

#include <fstream>

namespace Engine
{
	YAML::Emitter& operator << (YAML::Emitter& out, const math::Vec2& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << YAML::EndSeq;
		return out;
	}

	void SceneSerializer::SerializeGameObject(YAML::Emitter& out, GameObject& obj)
	{
// 		out << YAML::BeginMap;
// 		out << YAML::Key << "ID" << YAML::Value << obj.ID;
// 		out << YAML::Key << "Name" << YAML::Value << obj.DebugName;
// 
// 		// Transform
// 		out << YAML::Key << "Transform";
// 		out << YAML::Value;
// 		out << YAML::BeginMap;
// 		out << YAML::Key << "Position" << YAML::Value << obj.GetTransform().Position;
// 		out << YAML::Key << "Rotation" << YAML::Value << obj.GetTransform().Rotation;
// 		out << YAML::Key << "Scale" << YAML::Value << obj.GetTransform().Scale;
// 		out << YAML::EndMap;
// 
// 		// PhysicsBodyComponent
// 		//b2BodyType	BodyType = b2_staticBody;
// 		//bool			IsBullet = false;
// 		//uint16		CategoryBits = 0x0000; // I'm xxx
// 		//uint16		MaskBits = 0x0000; // I collide with yyy
// 
// 		auto* physicsBodyComponent = obj.GetComponent<PhysicsBodyComponent>();
// 		if (physicsBodyComponent)
// 		{
// 			out << YAML::Key << "PhysicsBodyComponent";
// 			out << YAML::Value;
// 			out << YAML::BeginMap;
// 			out << YAML::Key << "BodyType" << YAML::Value << static_cast<int>(physicsBodyComponent->m_bodyType);
// 			out << YAML::Key << "IsBullet" << YAML::Value << physicsBodyComponent->m_isBullet;
// 			out << YAML::Key << "CategoryBits" << YAML::Value << physicsBodyComponent->m_categoryBits;
// 			out << YAML::Key << "MaskBits" << YAML::Value << physicsBodyComponent->m_maskBits;
// 			out << YAML::EndMap;
// 		}
// 
// 		out << YAML::EndMap;
	}

	void SceneSerializer::Serialize(const std::string& filePath)
	{
		return;
		// ignore for this testing
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene";
		out << YAML::Value << "Untitled";
		out << YAML::Key << "GameObjects";
		out << YAML::Value << YAML::BeginSeq;

		// serialize all entities inside this scene
		for (auto gameobjectID : m_scene.m_gameObjects)
		{
			auto* gameobject = GameObjectManager::Get().GetGameObjectByID(gameobjectID);
			if (!gameobject)
				return; // is valid gameobject
			SerializeGameObject(out, *gameobject);
		}

		out << YAML::EndSeq;
		out << YAML::EndMap;

		std::ofstream fout(filePath);
		fout << out.c_str();
	}

	void SceneSerializer::Deserialize(const std::string& filePath)
	{

	}

}