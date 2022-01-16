#pragma once

namespace Engine
{
    class Application;
    class ApplicationInjection
    {
    public:
        virtual void RegisterGameComponents(Application& app) = 0;
        virtual void BeforeGameLoop(Application& app) = 0;
    };
};