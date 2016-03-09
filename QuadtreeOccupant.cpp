#include <QuadtreeOccupant.h>

#include <QuadtreeNodeTwo.h>

#include <Quadtree.h>

#include <assert.h>

using namespace ltbl;

void QuadtreeOccupant::quadtreeUpdate() {
    if (_pQuadtreeNodeTwo != nullptr)
        _pQuadtreeNodeTwo->update(this);
    else {
        _pQuadtree->_outsideRoot.erase(this);

        _pQuadtree->add(this);
    }
}

void QuadtreeOccupant::quadtreeRemove() {
    if (_pQuadtreeNodeTwo != nullptr)
        _pQuadtreeNodeTwo->remove(this);
    else
        _pQuadtree->_outsideRoot.erase(this);
}
