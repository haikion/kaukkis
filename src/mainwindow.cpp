#include <memory>
#include <QMessageBox>
#include <QDir>
#include <QPluginLoader>
#include <QDebug>
#include <QtGlobal>
#include <QCoreApplication>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "plugins/NetworkOutput/networkoutput.h" //TODO: Use dynamic loading instead

const QString MainWindow::PLUGINS_DIR = "plugins";

//Doesn't compile without this even with "std::" additions... go figure
using namespace std;
//FIXME: IconView in maemo
//FIXME: Portrait->landscape buttons get lost
//TODO: Detect keyboard out
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    pluginsDialog_(new PluginDialog(this))
{
    ui->setupUi(this);

    loadOutputPlugins();
    //TODO: Choose first one from all themes
    Remote* remote = new Remote("default", this);
    ui->graphicsView->setScene(remote);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    setupHildonMenu();

    QCoreApplication::setOrganizationName("org");
    QCoreApplication::setApplicationName("kaukkis");
    if ( QSettings().value("portrait", false).toBool() )
    {
        portraitMode();
    }
    else
    {
        landscapeMode();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showAbout()
{
    QMessageBox::about(this, "Authors", "Niko Häikiö (haikion@GitHub)");
}

void MainWindow::portraitMode()
{
    qDebug() << "MainWindow: PortraitMode() called";

    ui->menubar->removeAction(ui->actionPortrait);
    ui->menubar->addAction(ui->actionLandscape);
    setAttribute(QtCompatibility::WA_LockPortraitOrientation);
    QSettings().setValue("portrait", true);
}

void MainWindow::landscapeMode()
{
    qDebug() << "MainWindow: LandscapeMode() called";

    ui->menubar->removeAction(ui->actionLandscape);
    ui->menubar->addAction(ui->actionPortrait);
    setAttribute(QtCompatibility::WA_LockLandscapeOrientation);
    QSettings().setValue("portrait", false);
}
std::list<IRemoteOutput*> MainWindow::remoteOutputs() const
{
    return remoteOutputs_;
}

void MainWindow::setRemoteOutputs(const std::list<IRemoteOutput*>& remoteOutputs)
{
    remoteOutputs_ = remoteOutputs;
}


void MainWindow::addUseModeActions()
{
    ui->menubar->addAction(ui->actionEdit);
    ui->menubar->removeAction(ui->actionAddButton);
    ui->menubar->removeAction(ui->actionSave);
    ui->menubar->removeAction(ui->actionPlugins);
}

void MainWindow::useMode()
{
    addUseModeActions();
    activeRemote()->saveAndUse();
}

void MainWindow::editMode()
{
    ui->menubar->removeAction(ui->actionEdit);
    ui->menubar->addAction(ui->actionAddButton);
    ui->menubar->addAction(ui->actionSave);
    ui->menubar->addAction(ui->actionPlugins);
    activeRemote()->editMode();
}

//Loads given remote.
Remote* MainWindow::activeRemote( ) const
{
    return qobject_cast<Remote*>(ui->graphicsView->scene());
}

//Scans plugin dir for new plugins
void MainWindow::loadOutputPlugins()
{
    NetworkOutput* newPlugin = new NetworkOutput();
    remoteOutputs_.push_back(newPlugin);
    //remoteOutputs_.push_back(std::unique_ptr<IRemoteOutput>(newPlugin));
    //TODO: Uncomment and fix: "Is not a valid QT plugin
    /*
    bool rVal = false;

    qDebug() << "MainWindow: Loading plugins...";
    QDir fileBrowser(qApp->applicationDirPath());
    qDebug() << "MainWindow: loadOutputPlugins: current dir = " + fileBrowser.path();
    rVal = fileBrowser.cd(PLUGINS_DIR);
    qDebug() << "Opening dir: " + PLUGINS_DIR;
    Q_ASSERT_X(rVal, "MainWindow: loadOutputPlugins()", "PLUGINS_DIR doesn't exist");
    //Iterate through plugin directories
    for (QString pluginDir : fileBrowser.entryList(QDir::Dirs))
    {
        QDir fileBrowser2 = fileBrowser;
        rVal = fileBrowser2.cd(pluginDir);
        qDebug() << "Opening dir: " + pluginDir;
        Q_ASSERT_X(rVal, "MainWindow: loadOutputPlugins()", "Directory could not be opened.");
        //Open plugin files
        for (QString pluginFile : fileBrowser2.entryList(QDir::Files))
        {
            QPluginLoader pluginLoader(fileBrowser2.absoluteFilePath(pluginFile));
            QObject* plugin = pluginLoader.instance();
            qDebug() << "MainWindow: Error: " + pluginLoader.errorString();
            if (plugin)
            {
                qDebug() << "File: " + pluginFile + "is plugin file.";
                IRemoteOutput* newRemoteOutput = qobject_cast<IRemoteOutput*>(plugin);
                if (newRemoteOutput)
                {
                    std::unique_ptr<IRemoteOutput> uniqueRemote(newRemoteOutput);
                    qDebug() << "Loaded: " << newRemoteOutput->name() << " plugin.";
                    remoteOutputs_.push_back(std::move(uniqueRemote));
                }
            }
        }
    }
    */
}

std::vector<ButtonAction> MainWindow::avaibleButtonActions() const
{
    std::vector<ButtonAction> avaibleActions;

    //Gathers all actions from all remoteOutputs and combines them.
    for (const auto& ptr : remoteOutputs_)
    {
        std::vector<ButtonAction> actions =  ptr->buttonActions();
        avaibleActions.insert(avaibleActions.end(), actions.begin(), actions.end());
    }

    return avaibleActions;
}

//This function adds the status bar menu.
void MainWindow::setupHildonMenu()
{
    //About action is always visible
    ui->menubar->addAction(ui->actionAbout);
    //Connect actions
    connect(ui->actionEdit, SIGNAL(triggered()), this, SLOT(editMode()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(useMode()));
    connect(ui->actionAddButton, SIGNAL(triggered()), activeRemote(), SLOT(addButton()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));
    connect(ui->actionLandscape, SIGNAL(triggered()), this, SLOT(landscapeMode()));
    connect(ui->actionPortrait, SIGNAL(triggered()), this, SLOT(portraitMode()));
    connect(ui->actionPlugins, SIGNAL(triggered()), pluginsDialog_, SLOT(show()));
    //Use mode is the default mode
    addUseModeActions();
}
