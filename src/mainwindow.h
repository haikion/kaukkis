#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include <QGraphicsView>
#include <QMainWindow>
#include <QSettings>
#include "remote.h"
#include "iremoteoutput.h"
#include "plugindialog.h"
#include "themedialog.h"

namespace Ui {
class MainWindow;
}

//Compability fixes for QT 4.7 -> 4.8
//FIXME: QT5 compilation fails.
namespace QtCompatibility
{
#if QT_VERSION < 0x040702
    const Qt::WidgetAttribute WA_LockPortraitOrientation = Qt::WA_Maemo5PortraitOrientation;
    const Qt::WidgetAttribute WA_LockLandscapeOrientation = Qt::WA_Maemo5LandscapeOrientation;
    const Qt::WidgetAttribute WA_AutoOrientation = Qt::WA_Maemo5AutoOrientation;
#else
    const Qt::WidgetAttribute WA_LockPortraitOrientation = Qt::WA_LockPortraitOrientation;
    const Qt::WidgetAttribute WA_LockLandscapeOrientation = Qt::WA_LockLandscapeOrientation;
    const Qt::WidgetAttribute WA_AutoOrientation = Qt::WA_AutoOrientation;
#endif
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //Returns active remote.
    Remote* activeRemote() const;
    void loadOutputPlugins();
    std::vector<ButtonAction> avaibleButtonActions() const;
    std::vector<IRemoteOutput*> remoteOutputs() const;

private slots:
    void useMode();
    void editMode();
    void showAbout();
    void autoOrientation();
    void portraitMode();
    void landscapeMode();

private:
    static const std::vector<QString> PLUGINS_DIRS;

    Ui::MainWindow* ui;
    PluginDialog* pluginsDialog_;
    ThemeDialog* themeDialog_;
    //Use of unique_ptr causes double free error in destructor.
    //std::vector<std::unique_ptr<IRemoteOutput>> remoteOutputs_;
    std::vector<IRemoteOutput*> remoteOutputs_;

    void setupHildonMenu();
    void addUseModeActions();
};

#endif // MAINWINDOW_H
