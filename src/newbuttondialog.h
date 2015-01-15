#ifndef NEWBUTTONDIALOG_H
#define NEWBUTTONDIALOG_H

#include <QDialog>
#include <QListWidgetItem>
#include "theme.h"

namespace Ui {
class newButtonDialog;
}

class NewButtonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewButtonDialog(const Theme& theme, QWidget *parent = 0);
    ~NewButtonDialog();

    ButtonType selectedButton() const;

private:
    Ui::newButtonDialog *ui;
    ButtonType selectedButton_;

public slots:
    void chooseButton(QListWidgetItem* selection);
};

#endif // NEWBUTTONDIALOG_H
