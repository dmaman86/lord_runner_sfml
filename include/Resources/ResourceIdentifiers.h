#pragma once


// Forward declaration of SFML classes
namespace sf
{
	class Texture;
	class Font;
	class Shader;
	class SoundBuffer;
}


namespace ObjectType
{
	enum ID
	{
		PlayerChar = '@',
		MonsterChar = '%',
		FloorChar = '#',
		RopesChar = '-',
		LadderChar = 'H',
		CoinChar = '*'
	};
}

namespace Textures
{
	enum ID
	{
		TitleScreen,
		Menu,
		Game,
		Player,
		Monster,
		Coin,
		Ladder,
		Ropes,
		Wall
	};
}

namespace Fonts
{
	enum ID
	{
		Main,
	};
}

namespace SoundEffect
{
	enum ID
	{
		Open,
		Menu,
		Game,
		Button
	};
}

namespace Music
{
	enum ID
	{
		MenuTheme,
		MissionTheme,
	};
}


// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>			TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>					FontHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundEffect::ID>	SoundBufferHolder;
