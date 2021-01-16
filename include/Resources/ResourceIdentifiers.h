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
		CoinChar = '*',
		GiftChar = '+'
	};
}


namespace GiftType
{
	enum ID
	{
		addLife,
		addTime,
		addMonster
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
		Wall,
		Heart,
		Gifts,
		Stain
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
		Button,
		PlayerCoin,
		PlayerDead,
		PlayerInjured,
		StartLevelClock,
		EndTime
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
