# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = harbour-datameter

CONFIG += sailfishapp
QT += network

SOURCES += src/harbour-datameter.cpp \
    src/cyclichttprequest.cpp \
    src/networklistener.cpp \
    src/networkresponse.cpp \
    src/provider.cpp \
    src/provider/deutsche-telekom.cpp \
    src/provider/fake.cpp

DISTFILES += qml/harbour-datameter.qml \
    qml/cover/CoverPage.qml \
    qml/pages/FirstPage.qml \
    qml/pages/SecondPage.qml \
    rpm/harbour-datameter.changes.in \
    rpm/harbour-datameter.changes.run.in \
    rpm/harbour-datameter.spec \
    rpm/harbour-datameter.yaml \
    translations/*.ts \
    harbour-datameter.desktop

SAILFISHAPP_ICONS = 86x86 108x108 128x128 172x172

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n

# German translation is enabled as an example. If you aren't
# planning to localize your app, remember to comment out the
# following TRANSLATIONS line. And also do not forget to
# modify the localized app name in the the .desktop file.
TRANSLATIONS += translations/harbour-datameter-de.ts

HEADERS += \
    src/cyclichttprequest.h \
    src/networklistener.h \
    src/networkresponse.h \
    src/provider.h \
    src/provider/deutsche-telekom.h \
    src/provider/fake.h
