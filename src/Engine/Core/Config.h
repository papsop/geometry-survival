#pragma once
#include <string>

namespace Engine
{
	struct Config
	{
		
		// Window settings
		unsigned int	WindowWidth		= 680;
		unsigned int	WindowHeight	= 480;
		std::string		WindowName		= "NoName";
	};
};