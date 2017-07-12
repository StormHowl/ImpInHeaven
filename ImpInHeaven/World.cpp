﻿#include "World.h"


World::World()
{

}

void World::addElement(GameElement* element)
{
	this->entities.push_back(element);
}

void World::update(t_delta delta)
{
	for (auto element : entities)
	{
		handleElementEventsQueue(element);
		element->updateModifiers(delta);
	}

}

void World::render(t_delta delta)
{
	for (auto element : entities)
	{
		element->updateAccessors(delta);
	}
}

void World::handleEvent(SDL_Event* event)
{
	for (auto element : entities)
	{
		if (element->hasEventListener())
		{
			element->handleEvents(event);
		}
	}
}

void World::handleElementEventsQueue(GameElement* element) const
{
	while(element->hasEvent())
	{
		GameEvent event = element->popEvent();
		switch (event.type)
		{
		case MOVEMENT:
			if (validateMovement(element, event.input_action))
			{
				element->validateEvent(event);
			}
			break;
		case MOUSE_INPUT: 
			break;
		case TIME:
			element->validateEvent(event);
			break;
		default: ;
		}
	}
}

bool World::validateMovement(GameElement* element, EVENT_INPUT_ACTION movement) const
{
	Vector2<int> position = Vector2<int>(element->getPosition());

	switch(movement)
	{
	case MOVE_UP: 
		position._y -= 1;
		break;
	case MOVE_DOWN: 
		position._y += 1;
		break;
	case MOVE_LEFT: 
		position._x -= 1;
		break;
	case MOVE_RIGHT: 
		position._x += 1;
		break;
	case NO_ACTION: break;
	default: ;
	}

	changeElementDirection(position, element);

	if(checkInBounds(position))
	{
		if(!map->isWall(position))
		{
			//TODO Change it to post-handling (after moving the character)
			if (map->isTrap(position))
			{
				element->setState(DEAD);
			}

			return true;
		}
	}

	return false;
}

void World::changeElementDirection(Vector2<int> next_direction, GameElement* element)
{
	if (next_direction._x > element->getPositionX())
		element->setDirection(EAST);
	if (next_direction._x < element->getPositionX())
		element->setDirection(WEST);
	if (next_direction._y > element->getPositionY())
		element->setDirection(SOUTH);
	if (next_direction._y < element->getPositionY())
		element->setDirection(NORTH);
}

bool World::checkInBounds(Vector2<int> position) const
{
	return position.x() < map->getWidth() && position.x() >= 0 && position.y() < map->getHeight() && position.y() >= 0;
}

void World::setMap(Map* map)
{
	this->map = map;
}
