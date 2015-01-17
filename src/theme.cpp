#include <QDebug>
#include <QtGlobal>
#include "theme.h"

const QString Theme::THEME_DIR = "themes";
const QString Theme::RELEASED_FILE = "released.png";
const QString Theme::PRESSED_FILE = "pressed.png";
const QString Theme::BACKGROUND_FILE = "background.png";


Theme::Theme(QString name):
    name_(name)
{
    loadTheme();
}

QPixmap Theme::backgroundImage() const
{
    return backgroundImage_;
}

ButtonTheme Theme::buttonTheme(const ButtonType& type) const
{
    Q_ASSERT_X( buttonThemes_.size() != 0, "Theme::buttonTheme", "buttonTheme_ size is 0");
    Q_ASSERT_X( buttonThemes_.count(type) != 0, "Theme::buttonTheme", "Theme not found for a button!");
    return buttonThemes_.find(type)->second;
}

QString Theme::name() const
{
    return name_;
}
std::map<ButtonType, ButtonTheme> Theme::buttonThemes() const
{
    return buttonThemes_;
}

//Loads theme from image files.
//TODO: Implement theme chooser to allow multiple themes.
void Theme::loadTheme()
{
    //Specifies  theme dir for this specific theme.
    QString thisDir = THEME_DIR + "/" + name();
    //Load background image
    backgroundImage_.load(thisDir + "/" + "background.png");
    //Load button images
    for (auto it = BUTTON_NAMES.begin(); it != BUTTON_NAMES.end(); ++it)
    {
        ButtonType bt = it->first;
        QString buttonThemeDir = thisDir + "/" + it->second;
        ButtonTheme newTheme;
        newTheme.buttonType = bt;
        newTheme.imagePressed = QPixmap(buttonThemeDir + "/" + PRESSED_FILE);
        newTheme.imageReleased = QPixmap(buttonThemeDir + "/" + RELEASED_FILE);
        buttonThemes_[bt] = newTheme;
    }
    Q_ASSERT_X(buttonThemes_.size() != 0, "Theme::loadTheme", "ButtonThemes size is 0");
    qDebug() << "Theme: " << name_  << "loaded." << "Button theme count: " << buttonThemes_.size();
}