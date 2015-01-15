#include <QDebug>
#include <QDataStream>
#include <QByteArray>
#include <QMessageBox>
#include <QKeyEvent>
#include "message.h"
#include "networkoutput.h"
#include "ui_networkoutputdialog.h"

const QString NetworkOutput::NAME = "Network Output";
//Simply adding a key here should make it supported.
//There is a Qt::Key->xkeysym conversion function in server code which might need
//to be edided too.
const std::vector<Qt::Key> NetworkOutput::SUPPORTED_KEYS =
{
    //Numbers
    Qt::Key_0, Qt::Key_1, Qt::Key_2, Qt::Key_3, Qt::Key_4 ,Qt::Key_5, Qt::Key_6,
    Qt::Key_7, Qt::Key_8, Qt::Key_9,
    //Letters
    Qt::Key_A, Qt::Key_B, Qt::Key_C, Qt::Key_D, Qt::Key_E, Qt::Key_F, Qt::Key_G,
    Qt::Key_H, Qt::Key_I, Qt::Key_J, Qt::Key_K, Qt::Key_L, Qt::Key_M, Qt::Key_N,
    Qt::Key_O, Qt::Key_P, Qt::Key_Q, Qt::Key_R, Qt::Key_S, Qt::Key_T, Qt::Key_U,
    Qt::Key_W, Qt::Key_X, Qt::Key_Y, Qt::Key_Z,
    //Arrow Keys
    Qt::Key_Left, Qt::Key_Right, Qt::Key_Up, Qt::Key_Down,
    //Special keys
    Qt::Key_Space, Qt::Key_Enter, Qt::Key_Backspace, Qt::Key_Escape,
    //F keys
    Qt::Key_F1, Qt::Key_F2, Qt::Key_F3, Qt::Key_F4, Qt::Key_F5, Qt::Key_F6,
    Qt::Key_F7, Qt::Key_F8, Qt::Key_F9, Qt::Key_F10, Qt::Key_F11, Qt::Key_F12

};

NetworkOutput::NetworkOutput():
    dialog_(nullptr),
    ui_(new Ui::NetworkOutputDialog),
    settings_("org","kaukkis_network")
{
    buildButtonActions();
    loadSettings();
}

std::vector<ButtonAction> NetworkOutput::buttonActions() const
{
    return buttonActions_;
}

QString NetworkOutput::name() const
{
    return NAME;
}

void NetworkOutput::openSettingsDialog(QMainWindow* parent)
{
    if (dialog_ == nullptr)
    {
        dialog_ = new QDialog(parent);
        ui_->setupUi(dialog_);
    }
    ui_->ip->setText(client_.ip());
    ui_->port->setText(QString::number(client_.port()));
    if ( dialog_->exec() == 0)
    {
        return; //Rejected
    }
    //Accepted, collect settings.
    client_.setIp(ui_->ip->text());
    client_.setPort(ui_->port->text().toUInt());
    saveSettings();
}

//QSignalMapper doesn't support Qt::Key so
//we use int
void NetworkOutput::sendKeyPress(int keyInt)
{
    Qt::Key key = static_cast<Qt::Key>(keyInt);
    qDebug() << "NetworkOutput: Sending key press: " << QKeySequence(key).toString();

    Message newMsg(Message::Action::KEY_PRESS, key);
    if ( ! client_.sendMessage(newMsg) )
    {
        QMessageBox msg;
        msg.setText("NetworkOutput: Unable to send network message.");
        msg.exec();
    }
}

//QSignalMapper doesn't support Qt::Key so
//we use int
void NetworkOutput::sendKeyRelease(int keyInt)
{
    Qt::Key key = static_cast<Qt::Key>(keyInt);
    qDebug() << "NetworkOutput: Sending key release: " << QKeySequence(key).toString();

    Message newMsg(Message::Action::KEY_RELEASE, key);
    client_.sendMessage(newMsg);
}

void NetworkOutput::buildButtonActions()
{
    for (Qt::Key key : SUPPORTED_KEYS)
    {
        buttonActions_.push_back(generateButtonAction(key));
    }
}

ButtonAction NetworkOutput::generateButtonAction(const Qt::Key key)
{
    //Create QAction for the key press
    QAction* pressAction = new QAction(this);
    QSignalMapper* pressMapper = new QSignalMapper(this);
    connect(pressMapper, SIGNAL(mapped(int)), this, SLOT(sendKeyPress(int)));
    pressMapper->setMapping(pressAction, key);
    connect(pressAction, SIGNAL(triggered()), pressMapper, SLOT(map()));

    //Create QAction for the key release
    QAction* releaseAction = new QAction(this);
    QSignalMapper* releaseMapper = new QSignalMapper(this);
    connect(releaseMapper, SIGNAL(mapped(int)), this, SLOT(sendKeyRelease(int)));
    releaseMapper->setMapping(releaseAction, key);
    connect(releaseAction, SIGNAL(triggered()), releaseMapper, SLOT(map()));

    //Create button action
    ButtonAction newAction;
    newAction.name = QKeySequence(key).toString();
    newAction.pluginName = "Network Output";
    newAction.pressAction = pressAction;
    newAction.releaseAction = releaseAction;

    return newAction;
}

void NetworkOutput::saveSettings()
{
    settings_.setValue("ip", client_.ip());
    settings_.setValue("port", QString::number(client_.port()));
    settings_.sync(); //Needed?
    return;
}

bool NetworkOutput::loadSettings()
{
    if ( ! settings_.contains("ip") ||
         ! settings_.contains("port")
         )
    {
        return false;
    }
    client_.setIp(settings_.value("ip").toString());
    client_.setPort(settings_.value("port").toUInt());
    return true;
}
