#pragma once
#include "../Debug/Logger.h"

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

		inline void Lock() { m_locked = true; };
		inline void Unlock() { m_locked = false; };
		inline void EnsureLocked() { DD_ASSERT(!m_locked, "Manager is currently locked, this operation is blocked"); };

		bool m_initialized = false;
		bool m_locked = false;

	friend class Application; // only application should be able to init/destroy managers
	};

	class IManagerEditorWindow : public IManager
	{
	public:
		IManagerEditorWindow() = default;
		~IManagerEditorWindow() = default;

		void OnInit();
		void OnDestroy();
	};
};