#pragma once
#include "SteeringComponent.h"
class FleeComponent :
    public SteeringComponent
{
public:
    FleeComponent(Actor* target, float steeringForce, Actor* owner);

    MathLibrary::Vector2 calculateForce() override;
private:

};

