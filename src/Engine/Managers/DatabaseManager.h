#pragma once

namespace Engine
{
    class DatabaseManager
    {
    public:
        ~DatabaseManager() = default;
    private:
        DatabaseManager() = default;

        friend class Application;   // only Application can create a manager
    };
}