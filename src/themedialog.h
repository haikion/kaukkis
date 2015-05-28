#ifndef THEMEDIALOG_H
#define THEMEDIALOG_H

#include <vector>
#include <QDialog>
#include <QListWidgetItem>
#include <src/theme.h>
#include <src/remote.h>

namespace Ui {
class ThemeDialog;
}

class ThemeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ThemeDialog(QWidget *parent = 0);
    ~ThemeDialog();

    void setActiveRemote(Remote* remote);

private slots:
    void setTheme(QListWidgetItem* item);

private:
    Ui::ThemeDialog *ui;
    Remote* activeRemote_;

    static const std::vector<QString> THEMES_DIRS;

    void loadThemes();
};

#endif // THEMEDIALOG_H
