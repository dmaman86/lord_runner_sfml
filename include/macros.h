#pragma once

namespace Object_Direction
{
	enum ID
	{
		None = -1,
		Left = 1,
		Right = 2,
		Up = 3,
		Down = 4,
		Extra = 6
	};
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

namespace KindMonsters
{
	enum ID
	{
		Rand = 0,
		Horizontal,
		Smart,
		Max
	};
}

namespace KindGifts
{
	enum ID
	{
		Life,
		Time,
		Score,
		Monster,
		Stain,
		Max
	};
}

namespace SpecialKeyboard
{
	enum ID
	{
		DELETE_KEY = 8,
		ENTER_KEY = 13,
		ESCAPE_KEY = 27,
		MAX = 128
	};
}

namespace ButtonsMenu
{
	enum ID
	{
		PlayGame = 0,
		GameSettings,
		TopScores,
		Max
	};
}

namespace ButtonsSettings
{
	enum ID
	{
		AvailableMusic = 0,
		NoAvailableMusic,
		Max
	};
}

namespace ButtonsPause
{
	enum ID
	{
		BackToGame = 0,
		BackToMenu,
		Restart,
		Max
	};
}

const int MAX_LEVELS = 5;
const int MAX_LIFE = 6;
const int INIT_LIFE = 3;
const int INIT = 0;

