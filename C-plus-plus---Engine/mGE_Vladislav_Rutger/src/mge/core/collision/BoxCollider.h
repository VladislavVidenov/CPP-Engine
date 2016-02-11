#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H
#include <glm.hpp>
#include <Collider.h>


class BoxCollider : public Collider
{
    public:
        BoxCollider();
        virtual ~BoxCollider();

    void collide(Collider * pCollider);
    void collide(BoxCollider * pBoxCol);
    void collide(SphereCollider * pSphereCol);

    inline const glm::vec3 getMinBounds() const { return _minBounds; }
    inline const glm::vec3 getMaxBounds() const { return _maxBounds; }

    protected:
    private:
        glm::vec3 _minBounds;
        glm::vec3 _maxBounds;
};

#endif // BOXCOLLIDER_H
