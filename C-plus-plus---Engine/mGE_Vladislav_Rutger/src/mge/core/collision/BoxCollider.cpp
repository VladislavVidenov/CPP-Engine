#include "BoxCollider.h"
#include <iostream>
using namespace std;
BoxCollider::BoxCollider()
{
    //ctor
}

BoxCollider::~BoxCollider()
{
    //dtor
}
void BoxCollider::collide(Collider * pCollider)
{
    cout << "Double dispatch..." << endl;
    pCollider->collide(this);
}
void BoxCollider::collide(BoxCollider * pBoxCol)
{
    cout << "BoxCol.collides (BoxCol)" << endl;
    Collider::resolveCollision(this, pBoxCol);
}

void BoxCollider::collide(SphereCollider * pSphereCol)
{
    cout << "BoxCol.collides (pSphereCol)" << endl;
    Collider::resolveCollision(this, pSphereCol);
}
