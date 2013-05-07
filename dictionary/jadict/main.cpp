#include "dictwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dictWindow w;
    w.show();
    
    return a.exec();
}
