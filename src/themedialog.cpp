#include "themedialog.h"
#include "ui_themedialog.h"
#include <QDir>
#include <QDebug>

using namespace std;

const std::vector<QString> ThemeDialog::THEMES_DIRS = {"themes", "/usr/share/kaukkis/themes"};

ThemeDialog::ThemeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThemeDialog)
{
    ui->setupUi(this);

}

ThemeDialog::~ThemeDialog()
{
    delete ui;
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
        //Iterate through theme directories
        for (const QString& themeDir : fileBrowser.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
        {
            QDir fileBrowser2 = fileBrowser;
            bool rVal = fileBrowser2.cd(themeDir);
            Q_ASSERT_X(rVal, "ThemeDialog: loadThemes()", "Directory could not be opened.");
            qDebug() << "ThemeDialog: new theme found: " << themeDir;
            Theme* newTheme = new Theme(themeDir);
            //TODO: Check if theme was able to load
            themes.push_back(newTheme);
        }
    }
}
