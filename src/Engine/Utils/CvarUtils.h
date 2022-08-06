#pragma once
#include <string>
#include <memory>
#include <functional>

namespace Engine
{
	class I_Cvar
	{
	public:
		I_Cvar(std::string name)
			: m_key(name)
		{};

		virtual ~I_Cvar() = default;

		virtual void SetValueString(std::string value) = 0;
		virtual void SetValueFloat(float value) = 0;
		virtual void SetValueInt(int value) = 0;

		virtual std::string GetValueAsString() = 0;
		std::string GetKey() { return m_key; };
		bool IsDirty() { return m_isDirty; }
	protected:
		std::string m_key;
		bool m_isDirty = false;
	};

	template<typename T>
	class CvarWrapper final : public I_Cvar 
	{
	public:

		CvarWrapper(std::string key, T* ptr, T defaultValue, std::function<void(void)> func = nullptr);

		virtual ~CvarWrapper() override = default;

		virtual void SetValueString(std::string value) override;
		virtual void SetValueFloat(float value) override;
		virtual void SetValueInt(int value) override;

		virtual std::string GetValueAsString() override;
	private:
		void SetValue(T newValue);
		std::function<void(void)> m_onChanged;
		T* m_ptr;
	};

	CvarWrapper(const char*)->CvarWrapper<std::string>;
}

#include "CvarUtils.inl"