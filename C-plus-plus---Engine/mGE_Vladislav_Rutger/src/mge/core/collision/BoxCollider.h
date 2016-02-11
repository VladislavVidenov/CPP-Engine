#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include <Collider.h>


class BoxCollider : public Collider
{
    public:
        BoxCollider();
        virtual ~BoxCollider();


        void collide(Collider * pCollider);
        void collide(BoxCollider * pBoxCol);
        void collide(SphereCollider * pSphereCol);
    protected:
    private:
};

#endif // BOXCOLLIDER_H
