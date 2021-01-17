#pragma once


#include "Trophy.h"
#include "Resources/ResourceIdentifiers.h"

class DynamicObject;


class Gift : public Trophy
{
public:

	Gift(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt);
	virtual ~Gift();

	void resetExist() override;

	void virtual handleColision(DynamicObject& obj) = 0;

	void virtual handleColision(Player& obj) = 0;// needed override

	void virtual update() = 0;


	// static member function
//	static int getCount();  // return # objects instantiated
//	static int getCollected();
//	static void resetCollected();
protected:

private:

};