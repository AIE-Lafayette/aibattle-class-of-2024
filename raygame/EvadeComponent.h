#pragma once
#include "SteeringComponent.h"

class EvadeComponent :
    public SteeringComponent
{
public:
    EvadeComponent(Actor* target, float steeringForce, Actor* owner);

    MathLibrary::Vector2 calculateForce() override;
private:

};

