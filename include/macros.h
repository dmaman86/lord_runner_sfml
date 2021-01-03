#pragma once

const int NUM_BUTTONS = 9;

// char of objects
const char PLAYER = '@';
const char MONSTER = '%';
const char LADDER = 'H';
const char ROPES = '-';
const char EMPTY = ' ';
const char COIN = '*';
const char FLOOR = '#';

enum Options_in_Game {
	PLAYER_OP = 0,
	MONSTER_OP,
	COIN_OP,
	FLOOR_OP,
	ROPES_OP,
	LADDER_OP,
	EMPTY_OP,
	SAVE_OP,
	REFRESH_OP
};


