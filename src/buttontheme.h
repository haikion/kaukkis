/**
 * @(#) Buttontheme.h
 */

#ifndef BUTTONTHEME_H_H
#define BUTTONTHEME_H_H

#include <QPixmap>
#include "buttontype.h"

/**
 * Implements theme for remote Buttons
 */
struct ButtonTheme
{
    ButtonType buttonType;
    /**
     * Determines the image file that is displayed when button is held down.
     * TODO: Consider unique ptr option
     */
    QPixmap imagePressed;
    /**
     * Determines the image that is being displayed when button is up.
     */
    QPixmap imageReleased;
};

#endif
