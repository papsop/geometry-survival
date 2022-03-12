#include "QuadTree.h"

namespace Engine
{
    // Node stuff
    QTreeNode::QTreeNode(size_t depth, sf::Rect<float> rect)
        : c_depth(depth)
        , m_boundingBox(rect)
    {
        if (c_depth < 3)
        {
            Split();
        }
        
    }

    sf::Rect<float> QTreeNode::GenerateChildRect(size_t index)
    {
        auto rect = m_boundingBox;
        switch (index)
        {
            case 0:
                return sf::Rect<float>(rect.left, rect.top, rect.width / 2, rect.height / 2);
            case 1:
                return sf::Rect<float>(rect.left + rect.width / 2, rect.top, rect.width / 2, rect.height / 2);
            case 2:
                return sf::Rect<float>(rect.left, rect.top + rect.height / 2, rect.width / 2, rect.height / 2);
            case 3:
                return sf::Rect<float>(rect.left + rect.width / 2, rect.top + rect.height / 2, rect.width / 2, rect.height / 2);
            default:
                return {};
        }
    }

    void QTreeNode::Split()
    {
        size_t depth = c_depth+1;
        m_children[0] = std::make_unique<QTreeNode>(depth, GenerateChildRect(0));
        m_children[1] = std::make_unique<QTreeNode>(depth, GenerateChildRect(1));
        m_children[2] = std::make_unique<QTreeNode>(depth, GenerateChildRect(2));
        m_children[3] = std::make_unique<QTreeNode>(depth, GenerateChildRect(3));
    }

    void QTreeNode::Insert(GameObjectID id, const sf::Rect<float> boundingBox)
    {
        auto topLeft = GenerateChildRect(0);
        auto topRight = GenerateChildRect(1);
        auto bottomRight = GenerateChildRect(2);
        auto bottomLeft = GenerateChildRect(3);

        bool intersectsTopLeft = topLeft.intersects(boundingBox);
        bool intersectsTopRight= topRight.intersects(boundingBox);
        bool intersectsBottomRight = bottomRight.intersects(boundingBox);
        bool intersectsBottomLeft = bottomLeft.intersects(boundingBox);

        if (intersectsTopLeft)
        {
        }

    }

    void QTreeNode::Debug(view::IViewStrategy* viewStrategy)
    {
        // Top
        view::Line lineTop;
        lineTop.Points[0] = sf::Vector2f(m_boundingBox.left, m_boundingBox.top);
        lineTop.Points[1] = sf::Vector2f(m_boundingBox.left + m_boundingBox.width, m_boundingBox.top);
        // Bottom
        view::Line lineBottom;
        lineBottom.Points[0] = sf::Vector2f(m_boundingBox.left, m_boundingBox.top + m_boundingBox.height);
        lineBottom.Points[1] = sf::Vector2f(m_boundingBox.left + m_boundingBox.width, m_boundingBox.top + m_boundingBox.height);
        // Left
        view::Line lineLeft;
        lineLeft.Points[0] = sf::Vector2f(m_boundingBox.left, m_boundingBox.top);
        lineLeft.Points[1] = sf::Vector2f(m_boundingBox.left, m_boundingBox.top + m_boundingBox.height);
        // Right
        view::Line lineRight;
        lineRight.Points[0] = sf::Vector2f(m_boundingBox.left + m_boundingBox.width, m_boundingBox.top);
        lineRight.Points[1] = sf::Vector2f(m_boundingBox.left + m_boundingBox.width, m_boundingBox.top + m_boundingBox.height);

        viewStrategy->Render(lineTop);
        viewStrategy->Render(lineBottom);
        viewStrategy->Render(lineLeft);
        viewStrategy->Render(lineRight);
    }


    // Qtree stuff
    QTree::QTree(sf::Rect<float> rect)
        : m_boundingBox(rect)
    {
        m_root = std::make_unique<QTreeNode>(0, rect);
    }
};