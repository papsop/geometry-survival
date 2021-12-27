#include "BoxCollider.h"

#include "../../Core/GameObject.h"

namespace Game
{
    BoxCollider::BoxCollider(GameObject& obj)
        : IComponent(obj)
        , m_ownerTransform(obj.GetTransform())
    {

    }
};