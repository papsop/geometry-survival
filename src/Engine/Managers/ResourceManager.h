#pragma once
#include "IManager.h"
#include "ResourceTypes.h"
#include <SFML/Graphics.hpp>

#include <vector>

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
	class ResourceManager : public IManager
	{
	public:
		~ResourceManager() = default;

		template<typename T>
		ResourceHandle<T> LoadResource(const char* name);

		template<typename T>
		const T* GetResource(ResourceHandle<T> handle);

	protected:
		void VirtualOnInit() override;
		void VirtualOnDestroy() override;

	private:
		void LoadResources();
		ResourceManager() = default;

		std::map< uint32_t, void* > m_resourceContainers;

		const char* m_assetListFilePath = "assets/assetlist.yaml";

		friend class Application;
	};

}

#include "ResourceManager.inl"