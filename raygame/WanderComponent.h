#pragma once
#include "SteeringComponent.h"
#include <Vector2.h>

class WanderComponent :
    public SteeringComponent
{
public:
    WanderComponent(float circleRadius, float circleDistance, Actor* owner, float steeringForce);
    MathLibrary::Vector2 calculateForce();

    void draw() override;

private:
    float m_circleRadius;
    float m_circleDistance;
    float m_wanderAngle;

    MathLibrary::Vector2 m_circlePosition;


};

