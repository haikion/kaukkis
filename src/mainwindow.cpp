#include <memory>
#include <QMessageBox>
#include <QDir>
#include <QPluginLoader>
#include <QDebug>
#include <QtGlobal>
#include <QCoreApplication>
#include <set>
#include "mainwindow.h"
#include "ui_mainwindow.h"

const std::vector<QString> MainWindow::PLUGINS_DIRS = {"/usr/lib/kaukkis/plugins", "plugins"};

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

    if ( QSettings().value("orientation").toString() == "landscape" )
    {
        landscapeMode();
    }
    if ( QSettings().value("orientation").toString() == "portrait")
    {
        portraitMode();
    }
    else
    {
        autoOrientation();
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

void MainWindow::autoOrientation()
{
    qDebug() << "MainWindow: autoOrientation() called";

    ui->menubar->removeAction(ui->actionAutoOrientation);
    ui->menubar->addAction(ui->actionLandscape);
    ui->menubar->addAction(ui->actionPortrait);
    setAttribute(QtCompatibility::WA_AutoOrientation);
    QSettings().setValue("orientation", "auto");
}

void MainWindow::portraitMode()
{
    qDebug() << "MainWindow: PortraitMode() called";

    ui->menubar->removeAction(ui->actionPortrait);
    ui->menubar->addAction(ui->actionLandscape);
    ui->menubar->addAction(ui->actionAutoOrientation);
    setAttribute(QtCompatibility::WA_LockPortraitOrientation);
    QSettings().setValue("orientation", "portrait");
}

void MainWindow::landscapeMode()
{
    qDebug() << "MainWindow: LandscapeMode() called";

    ui->menubar->removeAction(ui->actionLandscape);
    ui->menubar->addAction(ui->actionPortrait);
    ui->menubar->addAction(ui->actionAutoOrientation);
    setAttribute(QtCompatibility::WA_LockLandscapeOrientation);
    QSettings().setValue("orientation", "landscape");
}
std::vector<IRemoteOutput*> MainWindow::remoteOutputs() const
{
    return remoteOutputs_;
}

void MainWindow::setRemoteOutputs(const std::vector<IRemoteOutput*>& remoteOutputs)
{
    remoteOutputs_ = remoteOutputs;
}


void MainWindow::addUseModeActions()
{
    ui->graphicsView->setBackgroundBrush(QBrush(Qt::NoBrush));
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
    ui->graphicsView->setBackgroundBrush(QBrush(Qt::darkYellow, Qt::SolidPattern));
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
    std::set<QString> pluginNames;

    QDir fileBrowser(qApp->applicationDirPath());

    qDebug() << "MainWindow: Loading plugins...current directory: " << fileBrowser.path();;

    for (const QString& pluginsDir : PLUGINS_DIRS)
    {
        if ( ! fileBrowser.cd(pluginsDir) )
        {
            qDebug() << "MainWindow: Unable to open directory: " << pluginsDir;
            continue;
        }
        qDebug() << "MainWindow: Opening directory: " << pluginsDir;
        //Iterate through plugin directories
        for (const QString& pluginDir : fileBrowser.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
        {
            QDir fileBrowser2 = fileBrowser;
            bool rVal = fileBrowser2.cd(pluginDir);
            qDebug() << "MainWindow: Opening plugin directory: " << pluginDir;
            Q_ASSERT_X(rVal, "MainWindow: loadOutputPlugins()", "Directory could not be opened.");
            //Open plugin files
            for (const QString& pluginFile : fileBrowser2.entryList(QDir::Files))
            {
                QPluginLoader pluginLoader(fileBrowser2.absoluteFilePath(pluginFile));
                QObject* plugin = pluginLoader.instance();
                if (plugin)
                {
                    qDebug() << "MainWindow: Detected plugin file: " << pluginFile;
                    IRemoteOutput* newRemoteOutput = qobject_cast<IRemoteOutput*>(plugin);
                    if (newRemoteOutput)
                    {
                        auto rVal = pluginNames.insert(newRemoteOutput->name());
                        if (rVal.second)
                        {
                            qDebug() << "MainWindow: Loaded " << newRemoteOutput->name() << " plugin.";
                            remoteOutputs_.push_back(newRemoteOutput);
                        }
                        else
                        {
                            qDebug() << "Duplicated plugin detected: " << newRemoteOutput->name();
                        }
                    }
                }
                else
                {
                    qDebug() << "MainWindow: Error loading plugin: " << pluginLoader.errorString();
                }
            }
        }
    }
    //NetworkOutput* newPlugin = new NetworkOutput();
    //remoteOutputs_.push_back(newPlugin);
    //remoteOutputs_.push_back(std::unique_ptr<IRemoteOutput>(newPlugin));
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
    connect(ui->actionPortrait, SIGNAL(triggered()), this, SLOT(portraitMode()));
    connect(ui->actionLandscape, SIGNAL(triggered()), this, SLOT(landscapeMode()));
    connect(ui->actionEdit, SIGNAL(triggered()), this, SLOT(editMode()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(useMode()));
    connect(ui->actionAddButton, SIGNAL(triggered()), activeRemote(), SLOT(addButton()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));
    connect(ui->actionAutoOrientation, SIGNAL(triggered()), this, SLOT(autoOrientation()));
    connect(ui->actionPlugins, SIGNAL(triggered()), pluginsDialog_, SLOT(show()));
    //Use mode is the default mode
    addUseModeActions();
}
