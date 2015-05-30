#include "themedialog.h"
#include "ui_themedialog.h"
#include <QDir>
#include <QDebug>
#include <memory>

using namespace std;

const std::vector<QString> ThemeDialog::THEMES_DIRS = {"themes", "/usr/share/kaukkis/themes"};

ThemeDialog::ThemeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThemeDialog)
{
    ui->setupUi(this);

    loadThemes();
    connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(setTheme(QListWidgetItem*)));
}

ThemeDialog::~ThemeDialog()
{
    while (ui->listWidget->count() > 0)
    {
        QListWidgetItem* item = ui->listWidget->takeItem(0);
        Theme* theme = (Theme*) item->data(Qt::UserRole).value<void*>();
        delete theme;
        delete item;
    }
    delete ui;
}

void ThemeDialog::setActiveRemote(Remote* remote)
{
    activeRemote_ = remote;
}

void ThemeDialog::setTheme(QListWidgetItem* item)
{
    Theme* selectedTheme = (Theme*) item->data(Qt::UserRole).value<void*>();
    qDebug() << "ThemeDialog: Setting theme: " << selectedTheme->name();
    activeRemote_->setTheme(selectedTheme);
    close();
}


void ThemeDialog::loadThemes()
{
    QDir fileBrowser(qApp->applicationDirPath());
    qDebug() << "ThemeDialog: Loading themes...current directory: " << fileBrowser.path();;

    for (const QString& themesDir : THEMES_DIRS)
    {
        qDebug() << "ThemeDialog: Opening directory: " << themesDir;
        if ( ! fileBrowser.cd(themesDir) )
        {
            qDebug() << "ThemeDialog: Unable to open directory: " << themesDir;
            continue;
        }
        //Iterate through theme directoriesF
        for (const QString& themeDir : fileBrowser.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
        {
            QDir fileBrowser2 = fileBrowser;
            bool rVal = fileBrowser2.cd(themeDir);
            Q_ASSERT_X(rVal, "ThemeDialog: loadThemes()", "Directory could not be opened.");
            qDebug() << "ThemeDialog: new theme found: " << themeDir;
            Theme* newTheme = new Theme(themeDir);
            //TODO: Check if theme was able to load
            QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
            item->setText(newTheme->name());
            item->setData(Qt::UserRole, qVariantFromValue((void*) newTheme));
            ui->listWidget->addItem(item);
        }
    }
}
