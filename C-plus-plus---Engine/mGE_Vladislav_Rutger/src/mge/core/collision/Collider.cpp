#include "Collider.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include <iostream>>
using namespace std;

Collider::Collider()
{
    //ctor
}

Collider::~Collider()
{
    //dtor
}

void Collider::resolveCollision (BoxCollider * colA, BoxCollider * colB)
{
    cout << "Solving Box to Box" << endl;
}

void Collider::resolveCollision (BoxCollider * colA, SphereCollider * colB)
{
    cout << "Solving Box to Sphere" << endl;
}

void Collider::resolveCollision (SphereCollider * colA, SphereCollider * colB)
{
    cout << "Solving Sphere to Sphere" << endl;
}
