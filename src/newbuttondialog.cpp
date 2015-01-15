#include <QPixmap>
#include <QListWidgetItem>
#include <QDebug>
#include "ui_newbuttondialog.h"
#include "newbuttondialog.h"
#include "buttontype.h"
#include "buttontheme.h"
#include "theme.h"

NewButtonDialog::NewButtonDialog(const Theme& theme, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newButtonDialog),
    selectedButton_(ButtonType::UNDEFINED)
{
    ui->setupUi(this);

    ui->listWidget->setViewMode(QListView::IconMode);
    //Construct selection menu.
    for (auto it = BUTTON_NAMES.begin(); it != BUTTON_NAMES.end(); ++it)
    {
        QString name = it->second;
        ButtonType bt = it->first;
        ButtonTheme buttonTheme = theme.buttonTheme(it->first);
        QPixmap image = buttonTheme.imageReleased;
        QListWidgetItem* item = new QListWidgetItem(QIcon(image), name, ui->listWidget);
        item->setData(Qt::UserRole, static_cast<unsigned>(bt));
        ui->listWidget->addItem(item);
    }

    connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(chooseButton(QListWidgetItem*)));
}

NewButtonDialog::~NewButtonDialog()
{
    delete ui;
}

ButtonType NewButtonDialog::selectedButton() const
{
    return selectedButton_;
}

void NewButtonDialog::chooseButton(QListWidgetItem* selection)
{
    qDebug() << "NewButtonDialog: chooseButton called";
    QVariant var = selection->data(Qt::UserRole);
    ButtonType bt = static_cast<ButtonType>(var.toUInt());
    selectedButton_ = bt;
    close();
}
