#pragma once

namespace States
{
    enum ID
    {
        Splash,
        Menu,
        Game,
        Pause,
        GameOver,
        GameWin,
        Records,
        AboutOur,
        Settings
    };
}

namespace StatesMenu
{
    enum ID
    {
        Game = 0,
        Settings,
        AboutOur,
        Records,
        Exit
    };
}