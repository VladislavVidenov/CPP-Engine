#include "SphereCollider.h"
#include <iostream>
using namespace std;
SphereCollider::SphereCollider()
{
    //ctor
}

SphereCollider::~SphereCollider()
{
    //dtor
}
void SphereCollider::collide(Collider * pCollider)
{
    cout << "Double dispatch..." << endl;
    pCollider->collide(this);
}
void SphereCollider::collide(BoxCollider * pBoxCol)
{
    cout << "SphereCol.collides (BoxCol)" << endl;
    Collider::resolveCollision(pBoxCol, this);
}

void SphereCollider::collide(SphereCollider * pSphereCol)
{
    cout << "SphereCol.collides (SphereCol)" << endl;
    Collider::resolveCollision(this, pSphereCol);
}
