#pragma once
#include "IManager.h"

namespace Engine
{
	class Application;

	class ResourceManager : public IManager
	{
	public:
		~ResourceManager() = default;

	protected:
		void VirtualOnInit() override;

	private:
		void LoadResources();
		ResourceManager() = default;


		const char* m_assetListFilePath = "assets/assetlist.yaml";
		friend class Application;
	};
}
