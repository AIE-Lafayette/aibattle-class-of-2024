#include "WanderComponent.h"
#include "Agent.h"
#include "Transform2D.h"
#include "MoveComponent.h"

#include <raylib.h>

#include <random>
#include <time.h>


WanderComponent::WanderComponent(float circleRadius, float circleDistance, Actor* owner, float steeringForce)
    : SteeringComponent(owner, steeringForce)
{
    m_circleDistance = circleDistance;
    m_circleRadius = circleRadius;
    m_wanderAngle = 0;

    srand(time(NULL));

    m_circlePosition = { 0 , 0 };
}

MathLibrary::Vector2 WanderComponent::calculateForce()
{
    if (getSteeringForce() == 0)
        return {0, 0};

    // find the agent's position and the direction it's moving in
    MathLibrary::Vector2 agentFacing = getAgent()->getTransform()->getForward();

    // find the circle's position in front of the agent
    MathLibrary::Vector2 agentPosition = getAgent()->getTransform()->getWorldPosition();
    m_circlePosition = agentPosition + agentFacing * m_circleDistance;

    // find a random direction in a unit circle
    int randInt = (rand() % 7); 
    float randFloat = (float)(rand()) / (float)(RAND_MAX);
    m_wanderAngle = randInt + randFloat;

    MathLibrary::Vector2 direction = MathLibrary::Vector2(cos(m_wanderAngle), sin(m_wanderAngle));

    // scale the random direction by the size of the circle.
    direction = direction * m_circleRadius;

    // add the random vector to the circle position to get a 
    // new random point on the edge of the circle
    MathLibrary::Vector2 targetPosition = m_circlePosition + direction;

    // seek to the random point

    // Grab the direction from the agent to the random point and apply it to seekForce
    MathLibrary::Vector2 directionToTarget = (targetPosition - agentPosition).getNormalized();
    MathLibrary::Vector2 wanderForce = directionToTarget * getSteeringForce();

    MathLibrary::Vector2 agentVelocity = getAgent()->getMoveComponent()->getVelocity();

    // Subtract the velocity of the agent from seekForce
    MathLibrary::Vector2 forceToApply = wanderForce - agentVelocity;

    return forceToApply;
}

void WanderComponent::draw()
{
    DrawCircleLines(m_circlePosition.x, m_circlePosition.y, m_circleRadius, RED);
}