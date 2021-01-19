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

const int MAX_LEVELS = 5;
const int MAX_LIFE = 6;
const int INIT_LIFE = 3;
const int INIT = 0;

