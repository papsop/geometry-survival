#pragma once
#include "IManager.h"
#include "../Debug/IDebuggable.h"

#include <SFML/Graphics.hpp>
#include <yaml-cpp/yaml.h>

#include <vector>
#include <memory>

namespace Engine
{
	class Application;
	struct AnimationSample;
	struct AnimationClip;

	// ============================
	// RESOURCE MANAGER
	// ============================
	class ResourceManager : public IManager, public IDebuggable
	{
	public:
		static ResourceManager& Get();
		~ResourceManager() = default;

		std::shared_ptr<sf::Texture> GetTexture(const char* name);
		std::shared_ptr<sf::Shader> GetShader(const char* name);
		std::shared_ptr<AnimationClip> GetAnimation(const char* name);

		void Debug(VisualDebugContext& debugContext) override;
	protected:
		void VirtualOnInit() override;
		void VirtualOnDestroy() override;

	private:
		ResourceManager() = default;

    void LoadResourcesList();
		void GenerateDummyResources();

		//
		// sf::Shader is noncopyable, so we can't return it from the function
		// BUT we need to change the already existing shader, so we need to pass a target pointer
		// to keep it the same, use the same process for textures
    void LoadTextureFromFile(sf::Texture* target, std::string filePath, bool isRepeatable);
		void LoadShaderFromFiles(sf::Shader* target, std::string fragmentPath, std::string vertexPath);
		
		void LoadAnimationData(AnimationClip* target, YAML::Node);

		std::unordered_map < std::string, std::shared_ptr<sf::Texture> > m_textures;
		std::unordered_map < std::string, std::shared_ptr<sf::Shader> > m_shaders;
		std::unordered_map < std::string, std::shared_ptr<AnimationClip> > m_animations;
	
		std::shared_ptr<sf::Texture> m_dummyTexture;

		const char* m_assetsFolder = "assets/";
		const char* m_texturesIndexPath = "assets/textures_index.yaml";
		const char* m_shadersIndexPath = "assets/shaders_index.yaml";
		const char* m_animationsIndexPath = "assets/animations_index.yaml";
		

		friend class Application;
	};

}

#include "ResourceManager.inl"