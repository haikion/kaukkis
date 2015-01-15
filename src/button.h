/**
 * @(#) Button.h
 */

#ifndef BUTTON_H_H
#define BUTTON_H_H

#include <memory>
#include <vector>
#include <QGraphicsPixmapItem>
#include <QMenu>
#include <QSettings>
#include "theme.h"
#include "buttondialog.h"
#include "buttonaction.h"
#include "buttontype.h"

class ButtonDialog;
class Remote;

//Implements remote button.
class Button: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Button(ButtonType type, ButtonTheme theme, QGraphicsScene* scene,
           QObject* parent = 0, QGraphicsItem* parent2 = 0);

    //Activates editing mode for the button.
    //Basically makes it movable and allows buttonDialog
    void editMode();
    void useMode();
    //Sets theme for the image a.k.a changes its image.
    void setTheme(const ButtonTheme& theme);
    ButtonType buttonType() const;
    QList<ButtonAction> buttonActions() const;
    void setButtonActions(const QList<ButtonAction>& buttonActions);
    std::vector<ButtonAction> availbleButtonActions() const;

    //These functions are called when the settings is handling this button
    //in order to load active actions.
    void saveActionSettings(QSettings* settings);
    void loadActionSettings(QSettings* settings);
protected:
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

private:
    QList<ButtonAction> buttonActions_;
    ButtonType type_;
    ButtonTheme theme_;
    //True if edit mode is active
    bool editingMode_;
    QMenu contextMenu_;
    std::unique_ptr<ButtonDialog> buttonDialog_;
    Remote* remote() const;

    //Returns ButtonAction with given pluginName and name. Returns empty buttonAction if
    //nothing was found.
    ButtonAction findButtonAction(const QString& pluginName, const QString& name) const;
private slots:
    void removeSelf();
};

#endif
