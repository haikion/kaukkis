/**
 * @(#) Remote.cpp
 */

#include <QDebug>
#include "remote.h"
#include "buttontype.h"
#include "newbuttondialog.h"
#include "mainwindow.h"

const QString Remote::ORGANIZATION = "org";
const QString Remote::APPLICATION = "kaukkis";

using namespace std;

Remote::Remote(QString name, QObject* parent):
    QGraphicsScene(parent),
    name_(name)
{
    //TODO: Set scene rect
    settings_ = std::unique_ptr<QSettings>(new QSettings(ORGANIZATION, APPLICATION, this));
    settings_->beginGroup(name_);
    loadSettings();
    newButtonDialog_ = std::unique_ptr<NewButtonDialog>(new NewButtonDialog(*theme_, mainWindow()));
}

//Adds new button to the remote.
//FIXME: Button spawns outside of the screen.
void Remote::addButton()
{
    newButtonDialog_->exec();
    ButtonType bt = newButtonDialog_->selectedButton();
    if (bt == ButtonType::UNDEFINED)
    {
        return; //User did not select the button.
    }
    Button* button = new Button(bt, theme_->buttonTheme(bt), this);
    button->editMode();
    qDebug() << "Added new button. Item count: " << items().size();
}

void Remote::removeButton(Button* button)
{
    qDebug() << "Remote: removeButton called";
    removeItem(button);
}

//Activates editing mode.
void Remote::editMode( )
{
    qDebug() << "Remote edit";
    //TODO: Change BG?
    for (Button* button : buttons())
    {
        button->editMode();
    }
}


//Sets theme for the remote.
void Remote::setTheme(std::unique_ptr<Theme> theme)
{
    theme_ = std::move(theme);
}

//Activates normal mode.
void Remote::useMode()
{
    //TODO: Change BG back to normal?
    for (Button* button : buttons())
    {
        button->useMode();
    }
}

//Saves and transfers to use mode
void Remote::saveAndUse()
{
    saveSettings();
    setSceneRect(itemsBoundingRect());
    useMode();
}

void Remote::addButtonAction(const ButtonAction& newAction)
{
    avaibleButtonActions_.push_back(newAction);
}

std::vector<ButtonAction> Remote::availableButtonsActions() const
{
    return mainWindow()->avaibleButtonActions();
}

void Remote::loadSettings( )
{
    //Test if saves exist
    if (! settings_->contains("theme"))
    {
        qDebug() << "Remote: Saves not found!";
        return;
    }

    QString themeName = settings_->value("theme").toString();
    unique_ptr<Theme> newTheme = std::unique_ptr<Theme>(new Theme(themeName));
    setTheme(move(newTheme));

    //Load all buttons for the remote.
    for (QString buttonSettings : settings_->childGroups())
    {
        settings_->beginGroup(buttonSettings);
        int posX = settings_->value("positionX").toInt();
        int posY = settings_->value("positionY").toInt();
        ButtonType type = static_cast<ButtonType>(settings_->value("buttonType").toUInt());
        Button* newButton = new Button(type, theme_->buttonTheme(type), this);
        newButton->setX(posX);
        newButton->setY(posY);
        newButton->loadActionSettings(settings_.get());
        settings_->endGroup();
    }
    qDebug() << "Remote: loaded " << buttons().size()  << " buttons";
}

void Remote::saveSettings( )
{
    qDebug() << "Remote: saving settings";
    //Clear old settings
    settings_->clear();

    settings_->setValue("theme", theme_->name());
    for (unsigned i = 0; i < buttons().size(); ++i )
    {
        Button* button = buttons().at(i);
        //Buttons don't have unique name so name them.
        //TODO: Consider moving button centric saves to button class.
        QString name = "button" + QString::number(i);
        settings_->beginGroup(name);
        settings_->setValue("positionX", button->x());
        settings_->setValue("positionY", button->y());
        settings_->setValue("buttonType", static_cast<unsigned>(button->buttonType()));
        button->saveActionSettings(settings_.get());
        settings_->endGroup();
    }
    settings_->sync();
    qDebug() << "Remote: saved settings.";
}

std::vector<Button*> Remote::buttons()
{
    std::vector<Button*> buttons;
    for ( QGraphicsItem* item : items() )
    {
        Button* button = qgraphicsitem_cast<Button*>(item);
        if (button != 0)
        {
            buttons.push_back(button);
        }
    }
    return buttons;
}

MainWindow* Remote::mainWindow() const
{
    return qobject_cast<MainWindow*>(parent());
}
