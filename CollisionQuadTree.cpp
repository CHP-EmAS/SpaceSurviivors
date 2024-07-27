#include "CollisionQuadTree.h"

bool CollisionQuadTree::insert(Node* node, const std::shared_ptr<GameObject>& object, int level)
{
    if (!node->bounds.intersects(object->getComponent<Collider>()->getAABB())) {
        return false;
    }

    if (node->objects.size() < maxObjects || level >= maxLevels) {
        node->objects.push_back(object);
        return true;
    }

    if (!node->children[0]) {
        subdivide(node);

        for (const auto& obj : node->objects) {
            insert(node, obj, level);
        }

        node->objects.clear();
    }

    for (int i = 0; i < 4; ++i) {
        insert(node->children[i].get(), object, level + 1);
    }

    return true;
}

void CollisionQuadTree::remove(Node* node, const std::shared_ptr<GameObject>& object)
{
    if (!node->bounds.intersects(object->getComponent<Collider>()->getAABB())) {
        return;
    }

    auto it = std::remove(node->objects.begin(), node->objects.end(), object);
    node->objects.erase(it, node->objects.end());

    if (!node->children[0]) {
        return;
    }

    for (int i = 0; i < 4; ++i) {
        remove(node->children[i].get(), object);
    }
}

void CollisionQuadTree::query(const Node* node, const sf::FloatRect& range, std::unordered_set<std::shared_ptr<GameObject>>& foundObjects) const
{
    if (!node->bounds.intersects(range)) {
        return;
    }

    for (const auto& object : node->objects) {
        if (range.intersects(object->getComponent<Collider>()->getAABB())) {
            foundObjects.insert(object);
        }
    }

    if (!node->children[0]) {
        return;
    }

    for (int i = 0; i < 4; ++i) {
        query(node->children[i].get(), range, foundObjects);
    }
}

void CollisionQuadTree::subdivide(Node* node)
{
    float x = node->bounds.left;
    float y = node->bounds.top;
    float width = node->bounds.width / 2.f;
    float height = node->bounds.height / 2.f;

    node->children[0] = std::make_unique<Node>(sf::FloatRect(x, y, width, height));
    node->children[1] = std::make_unique<Node>(sf::FloatRect(x + width, y, width, height));
    node->children[2] = std::make_unique<Node>(sf::FloatRect(x, y + height, width, height));
    node->children[3] = std::make_unique<Node>(sf::FloatRect(x + width, y + height, width, height));
}
