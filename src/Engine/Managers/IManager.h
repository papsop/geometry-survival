#pragma once

namespace Engine
{
	class Application;

	class IManager
	{
	public:
		bool IsInitialized() { return m_initialized; }
	protected:
		IManager() = default;
		~IManager() = default;

		virtual void OnInit() 
		{ 
			m_initialized = true;
		};
		virtual void OnDestroy() 
		{
			m_initialized = false;
		};
	private:
		bool m_initialized = false;

	friend class Application; // only application should be able to init/destroy managers
	};
};