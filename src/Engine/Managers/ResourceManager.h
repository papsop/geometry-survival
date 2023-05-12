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
	// RESOURCE MANAGER
	// ============================
	class ResourceManager : public IManager, public IDebuggable
	{
	public:
		static ResourceManager& Get();
		~ResourceManager() = default;

		std::shared_ptr<sf::Texture> ResourceManager::GetTexture(const char* name);
		std::shared_ptr<sf::Shader> ResourceManager::GetShader(const char* name);

		void Debug(VisualDebugContext& debugContext) override;
	protected:
		void VirtualOnInit() override;
		void VirtualOnDestroy() override;

	private:
		ResourceManager() = default;

    void LoadResourcesList();
		void GenerateDummyResources();

    std::shared_ptr<sf::Texture> LoadTextureFromFile(std::string filePath);
    std::shared_ptr<sf::Shader> LoadShaderFromFiles(std::string fragmentPath, std::string vertexPath);

		std::unordered_map < std::string, std::shared_ptr<sf::Texture> > m_textures;
		std::unordered_map < std::string, std::shared_ptr<sf::Shader> > m_shaders;
	
		std::shared_ptr<sf::Texture> m_dummyTexture;
		std::shared_ptr<sf::Shader>  m_dummyShader;

		const char* m_assetsFolder = "assets/";
		const char* m_texturesIndexPath = "assets/textures_index.yaml";
		const char* m_shadersIndexPath = "assets/shaders_index.yaml";
		

		friend class Application;
	};

}

#include "ResourceManager.inl"