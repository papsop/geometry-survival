#include "QuadTree.h"
#include <vector>
#include <algorithm>
namespace Engine
{
    std::unordered_map<void*, std::vector<QTreeNode<IColliderComponent>*>> QTree<IColliderComponent>::m_colliderToNodes = {};
};