#pragma once
#include <string>

namespace Engine
{
	struct C_Window
	{
		// Window settings
		unsigned int	Width		= 1024;
		unsigned int	Height		= 768;
		std::string		Name		= "Dungeons & Geometry";
		bool			Fullscreen	= false;
	};

	struct C_Engine
	{
		C_Window Window;
	};

	struct C_Game
	{
		// TODO custom game config
	};

	struct Config
	{
		C_Engine	Engine;
		C_Game		Game;
	};
};