#ifndef NETWORKOUTPUT_H
#define NETWORKOUTPUT_H

#include <vector>
#include <QString>
#include <QSignalMapper>
#include <QDialog>
#include <QSettings>
#include <QtCore/qplugin.h>
//#include "networkoutput_global.h"
#include "../../iremoteoutput.h"
#include "../../buttonaction.h"
#include "client.h"

namespace Ui {
    class NetworkOutputDialog;
}

//class NETWORKOUTPUTSHARED_EXPORT NetworkOutput : public QObject, public IRemoteOutput
class NetworkOutput : public QObject, IRemoteOutput
{

    Q_OBJECT
    Q_INTERFACES(IRemoteOutput)
//    Q_PLUGIN_METADATA(IID "org.kaukkis.NetworkOutput")

public:
    NetworkOutput();

    virtual std::vector<ButtonAction> buttonActions() const;
    virtual QString name() const;
    virtual void openSettingsDialog(QMainWindow* parent);

private slots:
    void sendKeyPress(int keyInt);
    void sendKeyRelease(int keyInt);

private:
    static const QString NAME;
    static const std::vector<Qt::Key> SUPPORTED_KEYS;

    std::vector<ButtonAction> buttonActions_;
    Client client_;
    QDialog* dialog_;
    Ui::NetworkOutputDialog* ui_;
    QSettings settings_;

    void buildButtonActions();
    ButtonAction generateButtonAction(const Qt::Key key);
    void saveSettings();
    bool loadSettings();
};
//Q_EXPORT_PLUGIN2(networkOutput, NetworkOutput)

#endif // NETWORKOUTPUT_H
