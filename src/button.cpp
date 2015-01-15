/**
 * @(#) Button.cpp
 */


#include <QDebug>
#include <QGraphicsSceneEvent>
#include <QGraphicsScene>
#include <QMenu>
#include <QtGlobal>
#include "button.h"
#include "remote.h"
#include "mainwindow.h"

Button::Button(ButtonType type, ButtonTheme theme,  QGraphicsScene* scene,
               QObject* parent, QGraphicsItem* parent2):
    QObject(parent),
    QGraphicsPixmapItem(parent2, scene),
    type_(type),
    editingMode_(false)
{
    setTheme(theme);
    buttonDialog_ = std::unique_ptr<ButtonDialog>(new ButtonDialog(this, remote()->mainWindow()));
    //Create right click menu
    QAction* customizeAction = new QAction("Customize", &contextMenu_);
    QAction* deleteAction = new QAction("Delete", &contextMenu_);
    contextMenu_.addAction(customizeAction);
    contextMenu_.addAction(deleteAction);
    ButtonDialog* buttonDialog = buttonDialog_.get();
    connect(customizeAction, SIGNAL(triggered()), buttonDialog, SLOT(show()));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(removeSelf()));
}

//Sets theme for the image a.k.a changes its image.
void Button::setTheme(const ButtonTheme& theme)
{
    theme_ = theme;
    setPixmap(theme_.imageReleased);
}

//Activates editing mode for the button. Basically makes it movable and allows buttonDialog
void Button::editMode( )
{
    qDebug() << "Button: editMode called";
    setFlag(GraphicsItemFlag::ItemIsMovable, true);
    editingMode_ = true;
}

void Button::useMode()
{
    setFlag(GraphicsItemFlag::ItemIsMovable, false);
    editingMode_ = false;
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    Q_UNUSED(event);
    qDebug() << "Button: Mouse press event";

    if (!editingMode_)
    {
        //Use Mode
        setPixmap(theme_.imagePressed);
        //Perform all press actions
        for ( const ButtonAction& action : buttonActions() )
        {
            action.pressAction->trigger();
        }
    }
}

void Button::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    qDebug() << "Button: Mouse release event";

    if (!editingMode_)
    {
        setPixmap(theme_.imageReleased);
        //Perform all release actions
        for ( const ButtonAction& action : buttonActions() )
        {
            action.releaseAction->trigger();
        }
    }
    QGraphicsPixmapItem::mouseReleaseEvent(event);
}

ButtonType Button::buttonType() const
{
    return type_;
}

QList<ButtonAction> Button::buttonActions() const
{
    return buttonActions_;
}

std::vector<ButtonAction> Button::availbleButtonActions() const
{
    return remote()->availableButtonsActions();
}

void Button::setButtonActions(const QList<ButtonAction>& buttonActions)
{
    buttonActions_ = buttonActions;
}


Remote* Button::remote() const
{
    return static_cast<Remote*>(scene());
}

void Button::removeSelf()
{
    qDebug() << "Button: removeSelf called";
    scene()->removeItem(this);
}

void Button::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
    Q_UNUSED(event);
    qDebug() << "Button: Context menu triggered";
    if (editingMode_)
    {
        contextMenu_.popup(event->screenPos());
    }
}

void Button::saveActionSettings(QSettings* settings)
{
    qDebug() << "Button: saveActionSettings called";
    settings->beginGroup("actions");
    for (int i = 0; i < buttonActions_.size(); ++i)
    {
        settings->beginGroup("action" + QString::number(i));
        ButtonAction bt = buttonActions_.at(i);
        settings->setValue("pluginName", bt.pluginName);
        settings->setValue("name", bt.name);
        settings->endGroup();
    }
    settings->endGroup();
}

void Button::loadActionSettings(QSettings *settings)
{
    qDebug() << "Button: loadActionSettings called. Current group: " << settings->group();
    settings->beginGroup("actions");
    for (QString actionSettings : settings->childGroups())
    {
        settings->beginGroup(actionSettings);
        ButtonAction bt = findButtonAction(settings->value("pluginName").toString(),
                                           settings->value("name").toString());
        if (bt.pluginName != "" && bt.name != "") //Test if anything was found.
        {
            buttonActions_.append(bt);
        }
        settings->endGroup();
    }
    settings->endGroup();
}

//Returns ButtonAction with given pluginName and name. Returns empty buttonAction if
//nothing was found.
ButtonAction Button::findButtonAction(const QString& pluginName, const QString& name) const
{
    qDebug().nospace() << "Button: Searching button action pluginName="
                       << pluginName << " name=" << name;
    for (ButtonAction bt : availbleButtonActions())
    {
        if (bt.pluginName == pluginName && bt.name == name)
        {
            return bt;
        }
    }
    //Return empty buttonAction if nothing was found.
    qDebug() << "Button: Not found";
    return ButtonAction();
}

