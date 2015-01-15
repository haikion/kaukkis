/**
 * @(#) ButtonAction.h
 */

#ifndef BUTTONACTION_H_H
#define BUTTONACTION_H_H

#include <QAction>

//Determines the actions that the button will do on press and on release.
struct ButtonAction
{
    QString name;
    QString pluginName;
    QAction* pressAction;
    QAction* releaseAction;

    bool operator==(const ButtonAction& comp) const
    {
        return comp.name == name;
    }

    ~ButtonAction()
    {
        //In QT 4 use of unique_ptr results in compilation
        //errors
        //delete pressAction;
        //delete releaseAction;
    }
};

#endif
