/**
 * @(#) IRemoteOutput.h
 */

#ifndef IREMOTEOUTPUT_H_H
#define IREMOTEOUTPUT_H_H


#include <QString>
#include <vector>
#include <QMainWindow>
#include "buttonaction.h"

/**
 * Interface that every remote output module needs to implement.
 * Remote output returns a list of Button actions which can be then added to the button.
 * name() returns the name of the output.
 * openSettingsDialog() opens a dialog where settings for the remote output can be changed.
 */
class IRemoteOutput
{
public:
    virtual std::vector<ButtonAction> buttonActions( ) const = 0;
    virtual QString name() const = 0;
    //mainWindow is used for settings dialog parent.
    virtual void openSettingsDialog(QMainWindow* mainWindow) = 0;
};


Q_DECLARE_INTERFACE(IRemoteOutput, "org.kaukkis/1.0");

#endif
