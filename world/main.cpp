#include <QtCore/qdir.h>
#include <QtQuick>

#include <QtGui/QGuiApplication>
#include <QtQuick/qquickview.h>
#include <qtquick2applicationviewer/qtquick2applicationviewer.h>

#include <QtCore/qdebug.h>
#include <QScreen>

#include <qtquick2applicationviewer/qtquick2applicationviewer.h>

#include <mesh.h>

int main(int argc, char *argv[])
{
    qmlRegisterType<Mesh>("CompPhys.World", 1, 0, "World");
    QGuiApplication app(argc, argv);

    QSurfaceFormat f;
    f.setMajorVersion(4);
    f.setMinorVersion(1);
//    f.setProfile(QSurfaceFormat::CoreProfile);
//    f.setProfile(QSurfaceFormat::CompatibilityProfile);
    QtQuick2ApplicationViewer view;
    // Specific to demo, not necessary after install
    view.addImportPath(".");
    // end specific to demo

    view.setFormat(f);
    view.setMainQmlFile("qml/world/main.qml");

    if (QGuiApplication::arguments().contains(QLatin1String("-maximize")))
        view.showMaximized();
    else if (QGuiApplication::arguments().contains(QLatin1String("-fullscreen")))
        view.showFullScreen();
    else
        view.show();

    return app.exec();
}
