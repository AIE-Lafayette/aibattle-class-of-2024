#pragma once
#include "SteeringComponent.h"

class PursueComponent :
    public SteeringComponent
{
public:
    PursueComponent(Actor* target, float steeringForce, Actor* owner);

    MathLibrary::Vector2 calculateForce() override;
private:

};

