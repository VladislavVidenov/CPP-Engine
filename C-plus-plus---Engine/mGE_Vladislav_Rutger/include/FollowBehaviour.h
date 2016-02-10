#ifndef FOLLOWBEHAVIOUR_H
#define FOLLOWBEHAVIOUR_H
#include <glm.hpp>
#include <mge/behaviours/AbstractBehaviour.hpp>


class FollowBehaviour : public AbstractBehaviour
{
    public:
        FollowBehaviour (GameObject * pTarget);
        virtual ~FollowBehaviour();

        virtual void update( float step );

    private:
        GameObject * _target;   //what are we looking at?
};

#endif // FOLLOWBEHAVIOUR_H
