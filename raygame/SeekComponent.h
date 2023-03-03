#pragma once
#include "SteeringComponent.h"
class SeekComponent :
    public SteeringComponent
{
public:
    SeekComponent(Actor* target, float steeringForce, Actor* owner);
       
    MathLibrary::Vector2 calculateForce() override;
private:

};

