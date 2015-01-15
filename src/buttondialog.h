/**
 * @(#) ButtonDialog.h
 */

#ifndef BUTTONDIALOG_H_H
#define BUTTONDIALOG_H_H

#include <vector>
#include <QDialog>
#include <QWidget>
#include "button.h"
#include "buttonaction.h"

namespace Ui {
class ButtonDialog;
}

class Button;

//Dialog for editing a button.
class ButtonDialog: public QDialog
{
    Q_OBJECT

public:
    ButtonDialog(Button* buttonParent, QWidget* widgetParent);
    Ui::ButtonDialog* ui;

private:
    Button* parent_;
    std::vector<ButtonAction> availableActions_;
public slots:
    void accepted();
    void show();
};

#endif
