/*
 * This is a stub for plugin development. It contains barebone of a plugin.
 * This stub is loadable by Kaukkis when placed in a correct directory.
 * When developing new plugin this stub should be copied, elements in it should be renamed after
 * which implementation can be done.
 */

#ifndef PLUGINSTUB_H
#define PLUGINSTUB_H

#include <QtCore/qplugin.h>
#include "../../iremoteoutput.h"
#include "../../buttonaction.h"

class PluginStub : public QObject, IRemoteOutput
{
    Q_OBJECT
    Q_INTERFACES(IRemoteOutput)

public:
    PluginStub();

    virtual std::vector<ButtonAction> buttonActions() const;
    virtual QString name() const;
    virtual void openSettingsDialog(QMainWindow* parent);
private:
    static const QString NAME;

    std::vector<ButtonAction> buttonActions_;
};

#endif // PLUGINSTUB_H
