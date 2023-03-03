#include "FleeComponent.h"
#include "Actor.h"
#include "Transform2D.h"
#include "Agent.h"
#include "MoveComponent.h"

FleeComponent::FleeComponent(Actor* target, float steeringForce, Actor* owner)
	: SteeringComponent(owner, steeringForce)
{
	setTarget(target);

}
MathLibrary::Vector2 FleeComponent::calculateForce()
{
	if (!getTarget() || getSteeringForce() == 0)
		return { 0,0 };

	// Cache agent and target positions for math
	MathLibrary::Vector2 agentPosition = getOwner()->getTransform()->getWorldPosition();
	MathLibrary::Vector2 targetPosition = getTarget()->getTransform()->getWorldPosition();

	// Grab the direction fgrom the agent to the target and apply it to seekForce
	MathLibrary::Vector2 directionToTarget = (agentPosition - targetPosition).getNormalized();
	MathLibrary::Vector2 seekForce = directionToTarget * getSteeringForce();

	MathLibrary::Vector2 agentVelocity = getAgent()->getMoveComponent()->getVelocity();

	// Subtract the velocity of the agent from seekForce
	MathLibrary::Vector2 forceToApply = seekForce - agentVelocity;

	return forceToApply;


}