#include "models/Object.h"

Object::Object(sf::Vector2f position, sf::Vector2f size, sf::Texture* txt)
{
	/*
	m_rec = new sf::Sprite;

	m_rec->setPosition(sf::Vector2f(position.x * size.x, position.y * size.y));

    m_rec->setTexture(*txt);

	m_rec->scale(size.x / txt->getSize().x, size.y / txt->getSize().y);
	m_rec->setOrigin(size.x / 2.f, size.y / 2.f);
	*/
	m_rec = new sf::Sprite;

	m_rec->setTexture(*txt);
	
	m_rec->setScale(sf::Vector2f(size.x / txt->getSize().x, size.y / txt->getSize().y));//15 / size.x, 25 / size.y);

	m_rec->setOrigin(sf::Vector2f(txt->getSize() / 2u));

	m_rec->setPosition
	(sf::Vector2f((position.x * size.x) + size.x / 2u, (position.y * size.y) + size.y / 2u));

}

Object::~Object()
{
	delete this->m_rec;
}

const sf::Vector2f& Object::getPositionRec()
{
	return m_rec->getPosition();
}

bool Object::collisionWith(const Object& obj) const
{
	return m_rec->getGlobalBounds().intersects(obj.m_rec->getGlobalBounds());
}

void Object::render(sf::RenderWindow* window)
{
	window->draw(*m_rec);
}



