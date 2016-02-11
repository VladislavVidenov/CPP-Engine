#ifndef COLLIDER_H
#define COLLIDER_H

class BoxCollider;
class SphereCollider;
class Collider
{
    public:
        Collider();
        virtual ~Collider() = 0;

        virtual void collide(Collider * pCollider) = 0;
        virtual void collide(BoxCollider * pBoxCol) = 0;
        virtual void collide(SphereCollider * pSphereCol) = 0;

    protected:
        void resolveCollision (BoxCollider * colA, BoxCollider * colB);
        void resolveCollision (BoxCollider * colA, SphereCollider * colB);
        void resolveCollision (SphereCollider * colA, SphereCollider * colB);
};

#endif // COLLIDER_H
