#pragma once
#include <stdint.h>

namespace Engine
{
    template<typename T>
    class IdGenerator
    {
    public:
        template<typename U>
        static uint32_t GetID()
        {
            static uint32_t ID = m_nextID++;
            return ID;
        }

    private:
        static uint32_t m_nextID;
    };

    template<typename T>
    uint32_t IdGenerator<T>::m_nextID = 0;
}
