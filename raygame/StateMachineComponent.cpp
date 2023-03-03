#include "StateMachineComponent.h"

StateMachineComponent::StateMachineComponent(Actor* owner) : Component() {}

void StateMachineComponent::start()
{
	Component::start();

	m_currentState = IDLE;
}
