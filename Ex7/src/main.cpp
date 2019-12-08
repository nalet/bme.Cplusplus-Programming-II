/****************************************************************************
** Copyright (c) 2018 HuCE-optoLab - Bern University of Applied Science
** Project: Example of a producer-comsumer-pattern
**
** Contact:    Patrik Arnold ( patrik.arnold@bfh.ch )
*****************************************************************************/
#include <QApplication>
#include <QFile>
#include "widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Set Style-sheet
    QFile File(":/BFH.stylesheet");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    qApp->setStyleSheet(StyleSheet);

    Widget w;
    w.show();
    return a.exec();
}
