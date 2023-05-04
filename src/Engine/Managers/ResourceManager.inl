#include "ResourceManager.h"

namespace Engine
{

	template<typename T>
	ResourceHandle<T> ResourceContainer<T>::LoadResource(const char* name)
	{
		uint32_t ID;
		if (m_resourceNameToID.find(name) != m_resourceNameToID.end())
		{
			// resource already loaded, just get ID
			ID = m_resourceNameToID[name];
		}
		else
		{
			// load resource, TODO fake for now
			ID = m_nextID++;

			T resource = LoadResourceImpl(name);
			
			m_resources[ID] = resource;
			m_resourceNameToID[name] = ID;
		}

		return ResourceHandle<T>(ID);
	}	

	// TODO: instead of returning nullptr, return a NULL OBJECT that has a dummy texture
// 	template<typename T>
// 	const T* ResourceContainer<T>::GetResource(ResourceHandle<T> handle)
// 	{
// 		if (m_resources.find(handle.ID) != m_resources.end())
// 			return &m_resources[handle.ID];
// 		else
// 			return nullptr;
// 	}
// 
// 	template<typename T>
// 	ResourceHandle<T> ResourceManager::LoadResource(const char* name)
// 	{
// 		auto ID = IdGenerator<ResourceManager>::GetID<T>();
// 
// 		if (m_resourceContainers.find(ID) == m_resourceContainers.end())
// 		{
// 			m_resourceContainers[ID] = new ResourceContainer<T>();
// 		}
// 
// 		auto* container = static_cast<ResourceContainer<T>*>(m_resourceContainers[ID]);
// 		return container->LoadResource(name);
// 	}
// 
// 	template<typename T>
// 	const T* ResourceManager::GetResource(ResourceHandle<T> handle)
// 	{
// 		auto ID = IdGenerator<ResourceManager>::GetID<T>();
// 
// 		if (m_resourceContainers.find(ID) == m_resourceContainers.end())
// 		{
// 			m_resourceContainers[ID] = new ResourceContainer<T>();
// 		}
// 
// 		auto* container = static_cast<ResourceContainer<T>*>(m_resourceContainers[ID]);
// 		return container->GetResource(handle);
// 	}

}