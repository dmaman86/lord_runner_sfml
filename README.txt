	OOP 1 Course - Lord Runner Game
=============================================
Name: David Maman, Id: 327437422
Name: Daniel Cohen, Id: 311551386
=============================================
General Explanation:


=============================================
Design:



================================================
List of files:

CMakeLists.txt
README.txt

File include:
Application.h
Board.h
CMakeLists.txt
ContainerStatus.h
ErrorState.h
FinalState.h
GameState.h
GetReadyState.h
InputManager.h
macros.h
MenuState.h
PauseState.h
PlayerInput.h
RecordsState.h
SettingsState.h
TitileState.h
1. Machine:
	State.h
	StateIdentifiers.h
	StateStack.h
2. models
	Coin.h
	DynamicObject.h
	Floor.h
	Gift.h
	GiftLife.h
	GiftMonster.h
	GiftScore.h
	GiftStain.h
	GiftTime.h
	Ladder.h
	Monster.h
	MonsterHorizontal.h
	MonsterRand.h
	MonsterSmart.h
	Object.h
	Player.h
	Ropes.h
	StaticObject.h
	Trophy.h
3. Recources
	ResourceHolder.h
	ResourceIdentifiers.h

File resources:
	fonts
	img
	levels
	records
	sounds

File src:
	like include file but here cpp files

================================================
Data Structures:
vector and map to manage states
map to manage sounds, textures and fonts
multimap to display scores 

================================================
Algorithms:
We used the BFS algorithm to find the closest way to the player.
We made conversions to fit for us.

Part of the match was to put the value 2 in a place that is "air" to
make the monster fall if the player is below it.
This addition also gives a way to "work" on the monster a bit

The algorithm works properly and really returns the first step
in the shortest trajectory, but it uses a two-dimensional matrix and
the conversion from it back to the window (in pixels) complicated us
a bit so we created a large function that tries to handle
the problematic cases.

Known bugs:
We know that we have not been able to cover all cases in a function
And we know that the monster sometimes gets stuck or does
things it is not supposed to do

================================================
Bugs:

================================================
Other:
