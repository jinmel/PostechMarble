#include "sellpopup.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.setApplication(&app);
    window.show();
    return app.exec();
}
