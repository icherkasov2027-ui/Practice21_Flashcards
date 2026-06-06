#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile styleFile(":/new/prefix1/style.qss");

    if (styleFile.open(QFile::ReadOnly)) {
        a.setStyleSheet(styleFile.readAll());
        styleFile.close();
        qDebug() << "Стиль успішно застосовано!";
    } else {
        qDebug() << "ПОМИЛКА: Не вдалося відкрити стиль!";
    }

    MainWindow w;
    w.show();
    return a.exec();
}
