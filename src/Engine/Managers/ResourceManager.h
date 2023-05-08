#pragma once
#include "IManager.h"
#include "ResourceTypes.h"
#include "../Debug/IDebuggable.h"

#include <SFML/Graphics.hpp>
#include <yaml-cpp/yaml.h>

#include <vector>
#include <memory>

namespace Engine
{
	class Application;

	// ============================
	// UTILS
	// ============================
	template<typename T>
	struct ResourceHandle
	{
		ResourceHandle(int h) : ID(h) {};

		const unsigned int ID;
	};

	template<typename T>
	class ResourceContainer
	{
	public:
		ResourceContainer() = default;
		~ResourceContainer() = default;

		ResourceHandle<T> LoadResource(const char* name);
		const T* GetResource(ResourceHandle<T> handle);
		
	private:
		T LoadResourceImpl(const char* name); // only allow specialized functions

		uint32_t m_nextID = 0;
		std::map<const char*, uint32_t> m_resourceNameToID;
		std::map<uint32_t, T> m_resources;
		
	};

	// ============================
	// RESOURCE MANAGER
	// ============================
	class ResourceManager : public IManager, public IDebuggable
	{
	public:
		static ResourceManager& Get();
		~ResourceManager() = default;

		//============================================================
		// TODO - implement
		//template<typename T>
		//ResourceHandle<T> LoadResource(const char* name);
		//template<typename T>
		//const T* GetResource(ResourceHandle<T> handle);
		//============================================================

		//============================================================
		// Placeholder resource management
		//============================================================
		std::shared_ptr<sf::Texture> ResourceManager::GetTexture(const char* name);
		std::shared_ptr<sf::Shader> ResourceManager::GetShader(const char* name);


		void Debug(VisualDebugContext& debugContext) override;

	protected:
		void VirtualOnInit() override;
		void VirtualOnDestroy() override;

	private:
		void LoadResourcesList();
		void LoadTextureResourceYAML(std::string topLevel, YAML::Node& node);
		void LoadShaderResourceYAML(std::string topLevel, YAML::Node& node);
		ResourceManager() = default;

		//std::map< uint32_t, void* > m_resourceContainers;
		std::unordered_map < std::string, std::shared_ptr<sf::Texture> > m_textures;
		std::unordered_map < std::string, std::shared_ptr<sf::Shader> > m_shaders;
		
		// std::unordered_map< std::string, std::string > m_resourceNamesToPaths;

		const char* m_assetListFilePath = "assets/assetlist.yaml";
		const char* m_assetsFolder = "assets/";

		friend class Application;
	};

}

#include "ResourceManager.inl"