#pragma once
#include "IBackendStrategy.h"
#include "../IDebuggable.h"
#include <string>
#include <vector>

namespace Engine 
{
    class WindowBackendStrategy : public IBackendStrategy, public IDebuggable
    {
    public:
        WindowBackendStrategy() = default;
        ~WindowBackendStrategy() override = default;

        void WriteText(LOGGER_LEVEL level, const char* source, const char* text) override;
        void Debug(view::IViewStrategy* viewStrategy) override;
    private:
        std::vector<std::string> m_texts;
    };
}


