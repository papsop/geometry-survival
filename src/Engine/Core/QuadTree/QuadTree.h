#pragma once
#include "../../Debug/IDebuggable.h"
#include "../GameObject/GameObject.h"

#include <SFML/Graphics.hpp>
#include <array>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace Engine
{
    const size_t QTREE_MAXDEPTH = 10;

    template<typename T>
    class QTreeNode : public IDebuggable
    {
    public:
        QTreeNode(size_t depth, sf::Rect<float> rect)
            : c_depth(depth)
            , m_boundingBox(rect)
        {
        }

        void Debug(view::IViewStrategy* viewStrategy)
        {
            //return;
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

            if (m_values.size() > 0)
            {
                // Count
                Transform t;
                t.Position = sf::Vector2f(m_boundingBox.left + m_boundingBox.width / 2, m_boundingBox.top + m_boundingBox.height / 2);
                view::Text textCount(t);
                textCount.Color = sf::Color::Red;
                textCount.ShouldCenter = true;
                textCount.Size = 17;
                textCount.Value = std::to_string(m_values.size());
                viewStrategy->Render(textCount);
            }

            viewStrategy->Render(lineTop);
            viewStrategy->Render(lineBottom);
            viewStrategy->Render(lineLeft);
            viewStrategy->Render(lineRight);
            
        }

        void Insert(T* value, const sf::Rect<float> boundingBox)
        {
            auto topLeft = GenerateChildRect(0);
            auto topRight = GenerateChildRect(1);
            auto bottomRight = GenerateChildRect(2);
            auto bottomLeft = GenerateChildRect(3);

            auto intersects = std::vector<bool>{ topLeft.intersects(boundingBox), topRight.intersects(boundingBox), bottomRight.intersects(boundingBox), bottomLeft.intersects(boundingBox) };
            size_t intersectsCount = std::count(intersects.begin(), intersects.end(), true);
            if (c_depth >= QTREE_MAXDEPTH || intersectsCount > 1)
            { // intersects multiple children or depth too high
                m_values.push_back(value);

                auto& nodes = QTree<T>::m_colliderToNodes[value];
                nodes.push_back(this);
            }
            else if (intersectsCount == 1)
            {
                if (!m_isSplit)
                    Split();
                for (size_t i = 0; i < m_children.size(); ++i)
                {
                    if (intersects[i])
                    {
                        m_children[i]->Insert(value, boundingBox);
                        break;
                    }
                }
            }
        }

        void Remove(T* value)
        {
            m_values.erase(std::remove(m_values.begin(), m_values.end(), value), m_values.end());
        }

        void QueryIntersections(sf::Rect<float> rect, std::unordered_set<T*>& values)
        {
            if (!m_boundingBox.intersects(rect)) return;

            for (auto& value : m_values)
            {
                values.insert(value);
            }

            if (m_isSplit)
            {
                for (size_t i = 0; i < m_children.size(); ++i)
                {
                    m_children[i]->QueryIntersections(rect, values);
                }
            }
        }

    private:
        sf::Rect<float> GenerateChildRect(size_t index)
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

        void Split()
        {
            size_t depth = c_depth + 1;
            m_children[0] = std::make_unique<QTreeNode<T>>(depth, GenerateChildRect(0));
            m_children[1] = std::make_unique<QTreeNode<T>>(depth, GenerateChildRect(1));
            m_children[2] = std::make_unique<QTreeNode<T>>(depth, GenerateChildRect(2));
            m_children[3] = std::make_unique<QTreeNode<T>>(depth, GenerateChildRect(3));
            m_isSplit = true;
        }

        sf::Rect<float> m_boundingBox;
        const size_t c_depth;
        
        //  0 | 1
        // -------
        //  3 | 2
        std::array<std::unique_ptr<QTreeNode<T>>, 4> m_children;
        std::vector<T*> m_values;
        bool m_isSplit = false;
    };

    template<typename T>
    class QTree
    {
    public:
        QTree(sf::Rect<float> rect)
            : m_boundingBox(rect)
        {
            m_root = std::make_unique<QTreeNode<T>>(0, rect);
        }

        void Insert(T* value, const sf::Rect<float> boundingBox)
        {
            m_root->Insert(value, boundingBox);
        }

        void Remove(T* value)
        {
            auto& arrNodes = m_colliderToNodes[value];
            for (auto& node : arrNodes)
            {
                node->Remove(value);
            }
            arrNodes.clear();
        }

        static std::unordered_map<void*, std::vector<QTreeNode<T>*>> m_colliderToNodes;

        std::unordered_set<T*> FindPossibleIntersections(sf::Rect<float> rect)
        {
            auto values = std::unordered_set<T*>();
            m_root->QueryIntersections(rect, values);
            return values;
        }

    private:
        sf::Rect<float> m_boundingBox;

        std::unique_ptr<QTreeNode<T>> m_root = nullptr;
    };

}


