#ifndef THEMEDIALOG_H
#define THEMEDIALOG_H

#include <QDialog>
#include <src/theme.h>
#include <vector>

namespace Ui {
class ThemeDialog;
}

class ThemeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ThemeDialog(QWidget *parent = 0);
    ~ThemeDialog();

private:
    Ui::ThemeDialog *ui;
    std::vector<Theme*> themes;
    static const std::vector<QString> THEMES_DIRS;

    void loadThemes();
};

#endif // THEMEDIALOG_H
