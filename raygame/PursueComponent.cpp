#include "PursueComponent.h"
#include "Actor.h"
#include "Transform2D.h"
#include "Agent.h"
#include "MoveComponent.h"

PursueComponent::PursueComponent(Actor* target, float steeringForce, Actor* owner)
	: SteeringComponent(owner, steeringForce)
{
	setTarget(target);

}

MathLibrary::Vector2 PursueComponent::calculateForce()
{
	if (!getTarget() || getSteeringForce() == 0)
		return { 0,0 };

	// Cache agent and target positions for math
	MathLibrary::Vector2 agentPosition = getOwner()->getTransform()->getWorldPosition();
	MathLibrary::Vector2 targetPosition = getTarget()->getTransform()->getWorldPosition();

	MoveComponent* targetMoveComponent = getTarget()->getComponent<MoveComponent>();

	// If the target has a move component, get the velocity from it. If not, the velocity is {0, 0}
	MathLibrary::Vector2 targetVelocity = targetMoveComponent ? targetMoveComponent->getVelocity() : MathLibrary::Vector2(0,0);
	
	// Grab the direction from the agent to the target and apply it to seekForce
	MathLibrary::Vector2 directionToTarget = targetPosition + targetVelocity - agentPosition;
	MathLibrary::Vector2 seekForce = directionToTarget.getNormalized() * getSteeringForce();

	MathLibrary::Vector2 agentVelocity = getAgent()->getMoveComponent()->getVelocity();

	// Subtract the velocity of the agent from seekForce
	MathLibrary::Vector2 forceToApply = seekForce - agentVelocity;

	return forceToApply;


}