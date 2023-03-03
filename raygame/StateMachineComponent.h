#include "Component.h"

enum State
{
	IDLE,
	WANDER,
	CHASE
};

class StateMachineComponent:
	public Component
{
public:
	StateMachineComponent(Actor* owner);

	void start() override;

	State getCurrentState() { return m_currentState; }
	void setCurrentState(State state) { m_currentState = state; }

private:
	State m_currentState;
};

