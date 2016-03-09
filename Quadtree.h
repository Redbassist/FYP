#pragma once

#include <QuadtreeNodeTwo.h>

#include <memory>

#include <unordered_set>
#include <list>

#include <mutex>
#include <thread>

namespace ltbl {
    class QuadtreeOccupant;

    // Base class for dynamic and static Quadtree types
    class Quadtree {
        friend class QuadtreeOccupant;
        friend class QuadtreeNodeTwo;
        friend class SceneObject;

    protected:
        std::unordered_set<QuadtreeOccupant*> _outsideRoot;

        std::unique_ptr<QuadtreeNodeTwo> _pRootNode;

        // Called whenever something is removed, an action can be defined by derived classes
        // Defaults to doing nothing
        virtual void onRemoval() {}

        void setQuadtree(QuadtreeOccupant* oc);

        void recursiveCopy(QuadtreeNodeTwo* pThisNode, QuadtreeNodeTwo* pOtherNode, QuadtreeNodeTwo* pThisParent);

    public:
        size_t _minNumNodeOccupants;
        size_t _maxNumNodeOccupants;
        size_t _maxLevels;

        float _oversizeMultiplier;

        Quadtree();
        Quadtree(const Quadtree &other) {
            *this = other;
        }

        virtual ~Quadtree() {}

        void operator=(const Quadtree &other);

        virtual void add(QuadtreeOccupant* oc) = 0;

        void queryRegion(std::vector<QuadtreeOccupant*> &result, const sf::FloatRect &region);
        void queryPoint(std::vector<QuadtreeOccupant*> &result, const sf::Vector2f &p);
        void queryShape(std::vector<QuadtreeOccupant*> &result, const sf::ConvexShape &shape);
    };
}
