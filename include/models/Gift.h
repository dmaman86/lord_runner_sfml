#pragma once


#include "Trophy.h"
#include "Resources/ResourceIdentifiers.h"

class DynamicObject;


class Gift : public Trophy
{
public:

	Gift(sf::Vector2f pos, sf::Vector2f size, sf::Texture* txt, GiftType::ID );
	virtual ~Gift();

	void resetExist() override;

//	void virtual handleColision(DynamicObject& obj) override;

	void virtual handleColision(Player& obj);// needed override

	void virtual update() = 0;

	bool isActive(GiftType::ID);

	// static member function
//	static int getCount();  // return # objects instantiated
//	static int getCollected();
//	static void resetCollected();
protected:
	static bool m_is_active;
	GiftType::ID m_type;
private:

};