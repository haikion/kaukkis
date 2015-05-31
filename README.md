
# Kaukkis
Kaukkis is a remote controller application for Maemo platform. It supports output plug-ins and theme plug-ins. It comes with a output plug-in to control X-window-system through a network.

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
Output plug-ins define functionality for button presses and releases. Button action defines QAction to be performed on button press and release. Users may choose which button actions are used for which button.
###Development
Kaukkis uses QT4's plug-in framework. Plug-in has to satisfy IRemoteOutput interface. Kaukkis will search for plug-in directories in following directories:
* [excutable location]/plugins
* /usr/lib/kaukkis/plugins

###Plug-in Stub
Plug-in stub has been created under src/plugins/PluginStub. This stub can be used as a base for a new plug-in. It should compile and load as a Kaukkis plug-in when placed in a correct directory.

##Themes
Kaukkis supports third party themes. Themes are defined as a series of button images. which are stored in following directories:
* [excutable location]/themes
* /usr/share/kaukkis/themes

###Development
In order to develop a new theme, one simply needs to create images for all of the buttons. Kaukkis uses the theme directory name as a name of the plugin. To get an idea of the directory structure of the theme please obverse the existing themes.

##Credits
Programming: Niko Häikiö (haikion@github) </br>
Kaukkis uses theme files from the Irreco project. These themes have been developed by following persons: </br>
* Modern (Kaukkis default theme): Miguel Peres 
* White: Teemu Hirvonen 
