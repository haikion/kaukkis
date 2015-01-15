/**
 * @(#) ButtonType.h
 */

#ifndef BUTTONTYPE_H_H
#define BUTTONTYPE_H_H
#include <map>
#include <QMetaType>

//Determines all the types for the button.
enum class ButtonType : unsigned
{
    UP,
    DOWN,
    RIGHT,
    LEFT,
    BLANK,
    OK,
    NEXT,
    PREV,
    MENU,
    PLAY,
    PLAY_PAUSE,
    POWER,
    NUMBER_1,
    NUMBER_2,
    NUMBER_3,
    NUMBER_4,
    NUMBER_5,
    NUMBER_6,
    NUMBER_7,
    NUMBER_8,
    NUMBER_9,
    UNDEFINED
};

//Gives each button a QString name for UI purposes
const std::map<ButtonType, QString> BUTTON_NAMES {
    {ButtonType::BLANK, "blank"},
    {ButtonType::DOWN, "down"},
    {ButtonType::LEFT, "left"},
    {ButtonType::MENU, "menu"},
    {ButtonType::NEXT, "next"},
    {ButtonType::NUMBER_1, "number_1"},
    {ButtonType::NUMBER_2, "number_2"},
    {ButtonType::NUMBER_3, "number_3"},
    {ButtonType::NUMBER_4, "number_4"},
    {ButtonType::NUMBER_5, "number_5"},
    {ButtonType::NUMBER_6, "number_6"},
    {ButtonType::NUMBER_7, "number_7"},
    {ButtonType::NUMBER_8, "number_8"},
    {ButtonType::NUMBER_9, "number_9"},
    {ButtonType::OK, "ok"},
    {ButtonType::PLAY, "play"},
    {ButtonType::PLAY_PAUSE, "play_pause"},
    {ButtonType::POWER, "power"},
    {ButtonType::PREV, "prev"},
    {ButtonType::RIGHT, "right"},
    {ButtonType::UP, "up"}
};

#endif
