#include "CvarUtils.h"

namespace Engine
{
// 	// Integer
// 	template<>
// 	void Engine::CvarWrapper<int>::SetValueInt(int value) 
// 	{
// 		*m_ptr = value; 
// 	}
// 
// 	template<>
// 	void Engine::CvarWrapper<int>::SetValueFloat(float value) 
// 	{ 
// 		*m_ptr = static_cast<int>(value); 
// 	}
// 
// 	template<>
// 	void Engine::CvarWrapper<int>::SetValueString(std::string value) 
// 	{ 
// 		*m_ptr = std::stoi(value.c_str()); 
// 	}
// 
// 	template<>
// 	std::string Engine::CvarWrapper<int>::GetValueAsString() { return std::to_string(*m_ptr); }
// 
// 	// Float
// 	template<>
// 	void Engine::CvarWrapper<float>::SetValueInt(int value) { *m_ptr = static_cast<float>(value); }
// 
// 	template<>
// 	void Engine::CvarWrapper<float>::SetValueFloat(float value) { *m_ptr = value; }
// 
// 	template<>
// 	void Engine::CvarWrapper<float>::SetValueString(std::string value) { *m_ptr = std::stof(value.c_str()); }
// 
// 	template<>
// 	std::string Engine::CvarWrapper<float>::GetValueAsString() { return std::to_string(*m_ptr); }
// 
// 	// String
// 	template<>
// 	void Engine::CvarWrapper<std::string>::SetValueInt(int value) { *m_ptr = std::to_string(value); }
// 
// 	template<>
// 	void Engine::CvarWrapper<std::string>::SetValueFloat(float value) { *m_ptr = std::to_string(value); }
// 
// 	template<>
// 	void Engine::CvarWrapper<std::string>::SetValueString(std::string value) { *m_ptr = value.c_str(); }
// 
// 	template<>
// 	std::string Engine::CvarWrapper<std::string>::GetValueAsString() { return *m_ptr; }
};