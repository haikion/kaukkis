/**
 * @(#) ThemeManager.cpp
 */


#include "thememanager.h"

static const QString THEME_DIR = "themes";
static const QString RELEASED_NAME = "released.png";
static const QString PRESSED_NAME = "pressed.png";

/**
 * Loads theme from image files.
 * TODO: Implement theme chooser to allow multiple themes.
 */
Theme ThemeManager::loadDefaultTheme() const
{
    //TODO: Create theme chooser
    Theme theme("default");
    return theme;
}

