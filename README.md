# Kaukkis
Kaukkis is a remote controller application for Maemo
platform. It supports output plugins and in the future will support theme
plugins. Currently there is only one output plugin
to control X-window-system through a network.

## Compilation
###Linux
####Requirements
* g++-4.6 or newer
* Qt4

####Compliation
```
qmake-qt4 kaukkisAndPlugins.pro
make
```

###Maemo
####Requirements
* g++-4.6 or newer

####Compilation under scratchbox
```
qmake kaukkisAndPlugins.pro
make
```
##Output plugins
Output plugins define functionality for button presses and releases. Button action defines QAction to be performed on button press and release. Users may choose which button actions are used for which button.
###Development
Kaukkis uses QT4's plugin framework. Plugin has to satisfy IRemoteOutput inteface. Kaukkis will search for plugin directories in following directories:
* <excutable location>/plugins
* /usr/lib/kaukkis/plugins

###Plugin Stub
Plugin stub has been created under src/plugins/PluginStub. This stub can be used as a base for a new plugin. It should compile and load as a kaukkis plugin when placed in a correct directory.