#pragma once

#include <optional>
#include <iostream>
#include <vector>
#include <memory>
#include <functional>

template <typename T, size_t Threshold>
class ObjectPool {
public:
    ObjectPool() {}

    std::optional<std::shared_ptr<T>> acquireObject() {
        if (availableObjects.empty()) {
            return std::nullopt;
        }

        auto obj = availableObjects.back();
        availableObjects.pop_back();
        return obj;
    }

    void releaseObject(std::shared_ptr<T> obj) {
        if (obj) {
            availableObjects.push_back(obj);
            if (availableObjects.size() > Threshold) {
                shrinkPool();
            }
        }
    }

    void clear() {
        availableObjects.clear();
    }

private:

    void shrinkPool() {
        while (availableObjects.size() > Threshold) {
            availableObjects.pop_back();
        }
    }

    std::shared_ptr<T> createObject() {
        return std::make_shared<T>();
    }

    std::vector<std::shared_ptr<T>> availableObjects;
};

