/**
 * @(#) theme.h
 */

#ifndef THEME_H_H
#define THEME_H_H

#include <QString>
#include <QPixmap>
#include <map>
#include "buttontheme.h"


//Implements theme for the remote.
class Theme
{
public:
    Theme(QString name);

    QPixmap backgroundImage() const;
    ButtonTheme buttonTheme(const ButtonType& type) const;
    QString name() const;
    std::map<ButtonType, ButtonTheme> buttonThemes() const;

private:
    static const QString BACKGROUND_FILE;
    //File name for given button
    static const QString PRESSED_FILE;
    //File name for given button
    static const QString RELEASED_FILE;
    //Holds path to the possible themes directories.
    //TODO: implement theme chooser to allow multiple themes.
    static const std::vector<QString> THEME_DIRS;

    //Determines the background image for the whole remote.
    QPixmap backgroundImage_;
    //Holds the name of the theme
    QString name_;
    //Connects each button to its theme object.
    std::map<ButtonType, ButtonTheme> buttonThemes_;

    //Loads theme from image files.
    void loadTheme();
};

#endif

