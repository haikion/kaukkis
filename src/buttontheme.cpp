#include "buttontheme.h"

const QString Theme::RELEASED_NAME = "released.png";
const QString ButtonTheme::PRESSED_NAME = "pressed.png";

ButtonTheme::ButtonTheme::ButtonTheme(ButtonType buttonType)
{
    imagePressed_.load(Theme::THEME_DIR + "/blank/" + RELEASED_NAME);
    imageReleased_.load(Theme::THEME_DIR + "/blank/" + PRESSED_NAME);
}

ButtonType ButtonTheme::buttonType() const
{
    return buttonType_;
}

QPixmap ButtonTheme::imagePressed() const
{
    return imagePressed_;
}

QPixmap ButtonTheme::imageReleased() const
{
    return imageReleased_;
}
