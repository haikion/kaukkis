#ifndef NETWORKOUTPUT_H
#define NETWORKOUTPUT_H

#include <vector>
#include <QString>
#include <QSignalMapper>
#include <QDialog>
#include "networkoutput_global.h"
#include "iremoteoutput.h"
#include "buttonaction.h"
#include "client.h"

namespace Ui {
    class NetworkOutputDialog;
}

class NETWORKOUTPUTSHARED_EXPORT NetworkOutput : public QObject, public IRemoteOutput
{

    Q_OBJECT
    Q_INTERFACES(IRemoteOutput)

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

#endif // NETWORKOUTPUT_H
