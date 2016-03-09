#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <newMath.h>

#include <memory>
#include <array>
#include <unordered_set>

namespace ltbl {
    class QuadtreeOccupant {
        friend class Quadtree;
        friend class QuadtreeNodeTwo;
        friend class DynamicQuadtree;
        friend class StaticQuadtree;

    private:
        class QuadtreeNodeTwo* _pQuadtreeNodeTwo;
        class Quadtree* _pQuadtree;

    public:
        QuadtreeOccupant()
            : _pQuadtreeNodeTwo(nullptr), _pQuadtree(nullptr)
        {}

        void quadtreeUpdate();
        void quadtreeRemove();

        virtual sf::FloatRect getAABB() const = 0;
    };
}
