/**
 * @(#) ButtonDialog.cpp
 */

#include <QDebug>
#include <map>
#include <QTreeWidgetItem>
#include <QTreeWidgetItemIterator>
#include "ui_buttondialog.h"
#include "buttondialog.h"
#include "buttonaction.h"

ButtonDialog::ButtonDialog(Button* buttonParent, QWidget* widgetParent):
    QDialog(widgetParent),
    ui(new Ui::ButtonDialog),
    parent_(buttonParent)
{
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accepted()));
}

void ButtonDialog::accepted()
{
    QList<ButtonAction> buttonActions;

    QTreeWidgetItemIterator it(ui->treeWidget, QTreeWidgetItemIterator::Checked);
    while (*it)
    {
        buttonActions.append(availableActions_[(*it)->data(0, Qt::UserRole).toInt()]);

        ++it;
    }
    parent_->setButtonActions(buttonActions);

    QWidget::close();
}

void ButtonDialog::show()
{
    QVector<QString> addedPlugins;

    qDebug() << "ButtonDialog: show called";
    ui->treeWidget->clear();
    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->setHeaderHidden(true);

    availableActions_ = parent_->availbleButtonActions();
    std::map<QString, std::vector<Button>> pluginMap;
    //Populate check list
    for (unsigned i = 0; i < availableActions_.size(); ++i)
    {
        ButtonAction buttonAction = availableActions_.at(i);
        //Find already added plugin, if it isn't found add it as top level item.
        QList<QTreeWidgetItem*> plugins = ui->treeWidget->findItems(buttonAction.pluginName, Qt::MatchExactly, 0);
        QTreeWidgetItem* plugin;
        if (plugins.size() > 0)
        {
            plugin = plugins.at(0);
        }
        else
        {
            plugin = new QTreeWidgetItem(ui->treeWidget);
            plugin->setText(0, buttonAction.pluginName);
            ui->treeWidget->addTopLevelItem(plugin);
        }
        QTreeWidgetItem* action = new QTreeWidgetItem();
        action->setText(0, buttonAction.name);
        action->setData(0, Qt::UserRole, qint32(i));
        //Set check state according to the button actions.
        action->setCheckState(0, Qt::Unchecked);
        if (parent_->buttonActions().contains(buttonAction))
        {
            action->setCheckState(0, Qt::Checked);
        }
        plugin->addChild(action);
    }

    QWidget::show();
}
