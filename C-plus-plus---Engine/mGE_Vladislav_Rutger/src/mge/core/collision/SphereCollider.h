#ifndef SPHERECOLLIDER_H
#define SPHERECOLLIDER_H

#include <Collider.h>


class SphereCollider : public Collider
{
    public:
        SphereCollider();
        virtual ~SphereCollider();

        void collide(Collider * pCollider);
        void collide(BoxCollider * pBoxCol);
        void collide(SphereCollider * pSphereCol);
    protected:
    private:
};

#endif // SPHERECOLLIDER_H
