#include <QListWidgetItem>
#include "mainwindow.h"
#include "iremoteoutput.h"
#include "plugindialog.h"
#include "ui_plugindialog.h"

PluginDialog::PluginDialog(MainWindow* parent) :
    QDialog(parent),
    parent_(parent),
    ui(new Ui::PluginDialog)
{
    ui->setupUi(this);

    connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(showPluginDialog(QListWidgetItem*)));
}

PluginDialog::~PluginDialog()
{
    delete ui;
}

void PluginDialog::show()
{
    ui->listWidget->clear();

    for (IRemoteOutput* output : parent_->remoteOutputs() )
    {
        QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
        item->setText(output->name());
        item->setData(Qt::UserRole, qVariantFromValue((void*) output));
        ui->listWidget->addItem(item);
    }

    QWidget::show();
}

void PluginDialog::showPluginDialog(QListWidgetItem* item)
{
    IRemoteOutput* output = (IRemoteOutput*) item->data(Qt::UserRole).value<void*>();
    output->openSettingsDialog(qobject_cast<QMainWindow*>(parent()));
}
