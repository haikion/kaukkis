#ifndef PLUGINDIALOG_H
#define PLUGINDIALOG_H

#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
class PluginDialog;
}

class MainWindow;

class PluginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PluginDialog(MainWindow* parent = 0);
    ~PluginDialog();

public slots:
    void show();
    void showPluginDialog(QListWidgetItem* item);

private:
    MainWindow* parent_;
    Ui::PluginDialog *ui;
};

#endif // PLUGINDIALOG_H
