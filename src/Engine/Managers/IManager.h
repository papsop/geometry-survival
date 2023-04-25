#pragma once

namespace Engine
{
	class Application;

	class IManager
	{
	public:
		IManager() = default;
		virtual ~IManager() = default;

		bool IsInitialized() { return m_initialized; }

		void OnInit()
		{
			VirtualOnInit();
			m_initialized = true;

		};
		void OnDestroy()
		{
			VirtualOnDestroy();
			m_initialized = false;
		};

		virtual void Update(float dt) { /* */ };
		virtual void FixedUpdate(float dt) { /* */ };
	protected:
		virtual void VirtualOnInit() { /* NO IMPLEMENTATION IN BASE CLASS */ };
		virtual void VirtualOnDestroy() { /* NO IMPLEMENTATION IN BASE CLASS */ };
		bool m_initialized = false;

	friend class Application; // only application should be able to init/destroy managers
	};
};