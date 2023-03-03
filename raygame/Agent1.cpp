#include "Agent1.h"
#include "SpriteComponent.h"
#include "SeekComponent.h"
#include "EvadeComponent.h"
#include "Goal.h"
#include "GameManager.h"
GameManager* gameInstance = GameManager::getInstance();

Agent1::Agent1(float x, float y, const char* name, float maxForce, float maxSpeed, float health) : Character(x, y, name, maxForce, maxSpeed, health)
{
	addComponent(new SpriteComponent("Images/player.png"));
}

void Agent1::onCollision(Actor* actor)
{
	Character::onCollision(actor);

	if(actor == gameInstance->getAgent2())
		gameInstance->getAgent2()->takeDamage();
}

void Agent1::start()
{
	Character::start();

	addComponent(new SeekComponent(gameInstance->getBall(), 1000, this));
	addComponent(new EvadeComponent(gameInstance->getAgent2(), 500, this));
	//add steering behaviours here
}

void Agent1::update(float deltaTime)
{
	Character::update(deltaTime);

	if (getHasBall())
	{
		getComponent<SeekComponent>()->setTarget(gameInstance->getRightGoal());
	}
	else
	{
		getComponent<SeekComponent>()->setTarget(gameInstance->getBall());
	}

}

void Agent1::onDeath()
{
	Character::onDeath();

}
