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

namespace MaxButtonsInState
{
	enum ID
	{
		SettingsButtons = 2,
		PauseButtons = 3,
		MenuButtons = 3
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

const int MAX_LEVELS = 5;
const int MAX_LIFE = 6;
const int INIT_LIFE = 3;
const int INIT = 0;

