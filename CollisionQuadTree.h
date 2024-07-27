#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_set>

#include "GameObject.h"

class CollisionQuadTree
{
public:
    CollisionQuadTree(const sf::FloatRect& bounds, int maxObjects = 4, int maxLevels = 5)
        : root(std::make_unique<Node>(bounds)), maxObjects(maxObjects), maxLevels(maxLevels) {}

    bool insert(const std::shared_ptr<GameObject>& object) {
        insert(root.get(), object, 0);
    }

    void remove(const std::shared_ptr<GameObject>& object) {
        remove(root.get(), object);
    }

    bool update(const std::shared_ptr<GameObject>& object) {
        remove(object);
        return insert(object);
    }

    void query(const sf::FloatRect& range, std::vector<std::shared_ptr<GameObject>>& foundObjects) const {
        std::unordered_set<std::shared_ptr<GameObject>> foundSet;
        query(root.get(), range, foundSet);
        foundObjects.assign(foundSet.begin(), foundSet.end());
    }
private:
    struct Node {
        sf::FloatRect bounds;
        std::list<std::shared_ptr<GameObject>> objects;
        std::unique_ptr<Node> children[4];

        Node(const sf::FloatRect& bounds) : bounds(bounds) {}
    };

    std::unique_ptr<Node> root;
    int maxObjects;
    int maxLevels;

    bool insert(Node* node, const std::shared_ptr<GameObject>& object, int level);
    void remove(Node* node, const std::shared_ptr<GameObject>& object);
    void query(const Node* node, const sf::FloatRect& range, std::unordered_set<std::shared_ptr<GameObject>>& foundObjects) const;

    void subdivide(Node* node);
};

