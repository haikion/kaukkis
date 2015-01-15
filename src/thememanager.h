/**
 * @(#) ThemeManager.h
 */

#ifndef THEMEMANAGER_H_H
#define THEMEMANAGER_H_H

#include <QString>
#include <map>
#include "buttontype.h"
#include "theme.h"

/**
 * This class handles the connection between styles and their image files.
 */
class ThemeManager
{
public:
    /**
     * Loads theme from image files.
     * TODO: Implement theme chooser to allow multiple themes.
     */
    Theme loadDefaultTheme() const;
    
private:
    /**
     * This map converts ButtonType to its string name.
     */
    std::map<ButtonType, QString> buttonStringName;
    
    /**
     * This is the postfix that is combined with the button type name string in order to figure out the image file name. This is for the pressed button.
     */
    static const QString PRESSED_POSTFIX;
    
    /**
     * This is the postfix that is combined with the button type name string in order to figure out the image file name. This is for the released button.
     */
    static const QString RELEASED_POSTFIX;
    
    /**
     * Holds path to the theme directory.
     * TODO: Replace with themes directory and use file handling to load all of the themes.
     */
    static const QString THEME_DIR;
};

#endif
