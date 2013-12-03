#include "sellpopup.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Sellpopup window;
    //window.setApplication(&app);
    window.show();
    return app.exec();
}
