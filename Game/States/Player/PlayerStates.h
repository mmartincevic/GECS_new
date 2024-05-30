#ifndef PLAYERSTATES_H__
#define PLAYERSTATES_H__

#pragma once

enum class PlayerStates {
    NONE = 0,
    IDLE,
    JUMPING,
    FALLING,
    RIGHT,
    LEFT,
    CROUCH
};

#endif