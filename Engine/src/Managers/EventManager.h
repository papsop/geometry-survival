#pragma once

namespace Engine
{
    class Application;
    class EventManager
    {
    public:
        ~EventManager() = default;

        static EventManager& Get();

    private:
        EventManager();

    friend class Application;
    };
}
