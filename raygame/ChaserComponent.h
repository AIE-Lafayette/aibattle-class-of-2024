#include "Component.h"

class StateMachineComponent;
class PursueComponent;
class WanderComponent;
class Agent;
class MoveComponent;

class ChaserComponent
	: public Component
{
public:
	ChaserComponent(float chaseRange, Actor* target, Actor* owner);

	PursueComponent* getPursueComponent() { return m_pursueComponent; }
	WanderComponent* getWanderComponent() { return m_wanderComponent; }

	float getChaseRange() { return m_chaseRange; }
	void setChaseRange(float chaseRange) { m_chaseRange = chaseRange; }
	                                        
	float getPursueForce() { return m_pursueForce; }
	void setPursueForce(float pursueForce) { m_pursueForce = pursueForce; }

	float getWanderForce() { return m_wanderForce; }
	void setWanderForce(float wanderForce) { m_wanderForce = wanderForce; }


	Actor* getTarget();

	void update(float deltaTime) override;

private:
	StateMachineComponent* m_stateMachine;

	PursueComponent* m_pursueComponent;
	Agent* m_agent;
	WanderComponent* m_wanderComponent;

	float m_wanderTime = 3;
	float m_currentTime = 0;

	float m_pursueForce = 50;
	float m_wanderForce = 100;
	float m_wanderCircleDistance = 100;
	float m_wanderCircleRadius = 100;
	float m_chaseRange;
};

