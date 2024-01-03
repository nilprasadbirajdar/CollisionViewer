#include "stdafx.h"
#include "Collision_Viewer.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Collision_Viewer w;
    w.show();
    return a.exec();
}
