#ifndef TILLERIMGUI_H
#define TILLERIMGUI_H

#pragma once

#include "../Resources/SDLImgui.h"
#include "imgui/imgui.h"


class TillerImgui : public SDLImguiMenuItem
{
public:

    const char* GetName() const override {
        return "Tiles";
    }

    virtual void RenderWindow() override;

};

#endif