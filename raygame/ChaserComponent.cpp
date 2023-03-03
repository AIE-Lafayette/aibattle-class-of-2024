#include "ChaserComponent.h"
#include "PursueComponent.h"
#include "WanderComponent.h"
#include "MoveComponent.h"
#include "StateMachineComponent.h"
#include "Transform2D.h"
#include "Actor.h"
#include "Agent.h"

ChaserComponent::ChaserComponent(float chaseRange, Actor* target, Actor* owner) : Component()
{
	m_chaseRange = chaseRange;

	m_pursueComponent = (PursueComponent*)owner->addComponent(new PursueComponent(target, m_pursueForce, owner));
	m_wanderComponent = (WanderComponent*)owner->addComponent(new WanderComponent(m_wanderCircleDistance, m_wanderCircleRadius, owner, m_wanderForce));
	m_stateMachine = (StateMachineComponent*)owner->addComponent(new StateMachineComponent(owner));

	m_agent = m_pursueComponent->getAgent();
}

Actor* ChaserComponent::getTarget() { return m_pursueComponent->getTarget(); }

void ChaserComponent::update(float deltaTime)
{
	MathLibrary::Vector2 targetPosition = getTarget()->getTransform()->getWorldPosition();
	MathLibrary::Vector2 ownerPosition = getOwner()->getTransform()->getWorldPosition();

	float distanceFromTarget = (targetPosition - ownerPosition).getMagnitude();

	bool targetInRange = distanceFromTarget <= m_chaseRange;

	switch (m_stateMachine->getCurrentState())
	{
	case IDLE:
		m_wanderComponent->setSteeringForce(0);
		m_pursueComponent->setSteeringForce(0);

		if (targetInRange)
			m_stateMachine->setCurrentState(CHASE);

		break;
	case CHASE:
		m_wanderComponent->setSteeringForce(0);
		m_pursueComponent->setSteeringForce(m_pursueForce);   

		if (!targetInRange)
			m_stateMachine->setCurrentState(WANDER);

		break;
	case WANDER:
		m_wanderComponent->setSteeringForce(m_wanderForce);
		m_pursueComponent->setSteeringForce(0);
		
		m_currentTime += deltaTime;


		if (targetInRange)
		{
			m_stateMachine->setCurrentState(CHASE);
		}
		else if (m_currentTime >= m_wanderTime)
		{
			m_stateMachine->setCurrentState(IDLE);
			m_currentTime = 0;
		}

		break;
	}
}