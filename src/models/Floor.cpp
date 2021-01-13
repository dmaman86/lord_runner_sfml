#include "models/Floor.h"

Floor::Floor(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt) :
	StaticObject(pos, size, txt)
{
	this->m_rec->setScale(m_rec->getScale().x * 1, m_rec->getScale().y * 0.6);
}

void Floor::handleColision(DynamicObject& obj)
{
	obj.handleColision(*this);
}
/*
bool Flor::collisionWithStand(const sf::Vector2f v2f, const sf::Vector2f size)
{
	return this->getGlobBounds().contains
	(v2f.x , v2f.y + size.y);
}
*/
bool Floor::collisionWithStand(DynamicObject& obj, sf::Vector2f size)
{	
	//return false;
	//sf::RectangleShape helpRec;
	sf::Sprite helpRec(obj.getSprite());
	//helpRec.setOrigin(sf::Vector2f(size.x / 2.f, size.y / 2.f));
	
	//helpRec.setScale(helpRec.getScale().x * 1, helpRec.getScale().y * 0.8);

	helpRec.move(sf::Vector2f(0, 4.5));
	//helpRec.setPosition
	//(sf::Vector2f(obj.getSprite().getPosition().x, obj.getSprite().getPosition().y + (size.y / 25.f)));

	return this->m_rec->getGlobalBounds().intersects(helpRec.getGlobalBounds());
}

