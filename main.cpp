#include <QtWidgets/QApplication>
#include "CQmlAdapter.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    CQmlAdapter cQmlAdapter;

    return app.exec();
}
