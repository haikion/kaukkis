/**
 * @(#) Remote.h
 */

#ifndef REMOTE_H_H
#define REMOTE_H_H

#include <vector>
#include <memory>
#include <QGraphicsScene>
#include <QSettings>
#include "theme.h"
#include "button.h"
#include "newbuttondialog.h"

class MainWindow;

//implements remote UI
class Remote: public QGraphicsScene
{
    Q_OBJECT

public:
    explicit Remote(QString name, QObject* parent = 0);

    //Activates editing mode.
    void editMode();
    //Sets theme for the remote.
    void setTheme(Theme* theme);
    //Activates normal mode.
    void useMode();
    std::vector<ButtonAction> availableButtonsActions() const;
    void saveAndUse();
    void addButtonAction(const ButtonAction& newAction);
    MainWindow* mainWindow() const;

public slots:
    //Adds new button to the remote.
    void addButton();
    void removeButton(Button* button);
    
private:
    static const QString ORGANIZATION;
    static const QString APPLICATION;

    QString name_;
    std::unique_ptr<QSettings> settings_;
    Theme* theme_;
    std::unique_ptr<NewButtonDialog> newButtonDialog_;
    std::vector<ButtonAction> avaibleButtonActions_;
    std::vector<Button*> buttons();

    void loadSettings();
    void saveSettings();
};

#endif
