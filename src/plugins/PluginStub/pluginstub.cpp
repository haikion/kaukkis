#include "pluginstub.h"

const QString PluginStub::NAME = "Plugin Stub";

PluginStub::PluginStub()
{
   //Build buttonActions and initialize everything.
}

//Button Actions define actions on remote button release and
//press.
std::vector<ButtonAction> PluginStub::buttonActions() const
{
    return buttonActions_;
}

QString PluginStub::name() const
{
    return NAME;
}

void PluginStub::openSettingsDialog(QMainWindow* parent)
{
   //Open settings dialog. Use parent parameter as parent if needed.
}

Q_EXPORT_PLUGIN2(pluginStub, PluginStub);
