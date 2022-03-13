#pragma once
#include "../../Debug/IDebuggable.h"
#include "../GameObject.h"

#include <SFML/Graphics.hpp>
#include <array>
namespace Engine
{
    const size_t QTREE_MAXDEPTH = 7;

    class QTreeNode : public IDebuggable
    {
    public:
        QTreeNode(size_t depth, sf::Rect<float> rect);
        void Debug(view::IViewStrategy* viewStrategy);

        void Insert(GameObjectID id, const sf::Rect<float> boundingBox);
    private:
        sf::Rect<float> GenerateChildRect(size_t index);
        void Split();

        sf::Rect<float> m_boundingBox;
        const size_t c_depth;
        
        //  0 | 1
        // -------
        //  3 | 2
        std::array<std::unique_ptr<QTreeNode>, 4> m_children;
        std::vector<GameObjectID> m_gameObjects;
        bool m_isSplit = false;
    };

    typedef std::unique_ptr<QTreeNode> ptr_QTreeNode;

    class QTree
    {
    public:
        QTree(sf::Rect<float> rect);
        void Insert(GameObjectID id, const sf::Rect<float> boundingBox);

    private:
        sf::Rect<float> m_boundingBox;

        ptr_QTreeNode m_root = nullptr;
    };

}


