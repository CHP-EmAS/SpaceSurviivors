#pragma once

#include <SFML/System/Vector2.hpp>

#define _USE_MATH_DEFINES 
#include <math.h>

class VectorExtension
{
public:
    static float dotP(sf::Vector2f v1, sf::Vector2f v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }

    static float vectorSquareLength(sf::Vector2f v) {
        return v.x * v.x + v.y * v.y;
    }

    static sf::Vector2f normalize(sf::Vector2f v)
    {
        float length = vectorSquareLength(v);

        if (length == 0.f) {
            return v;
        }
            
        length = sqrt(1.f / length);

        v.x = v.x * length;
        v.y = v.y * length;

        return v;
    }

 
    static float getAngle(sf::Vector2f direction) {
        float angle = atan2(direction.y, direction.x);
        float degrees = 180.f * angle / M_PI;
        return degrees;
    }

    static sf::Vector2f toUnitVector(float angleInDegrees) {
        float angleInRadians = angleInDegrees * M_PI / 180.f;
        float x = std::cos(angleInRadians);
        float y = std::sin(angleInRadians);
        return sf::Vector2f(x, y);
    }
};