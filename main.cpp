#include "mainwindow.h"
#include "testdatahandler.h"
#include <QApplication>
#include <QFile>
#include <QDebug>
#include <QtTest>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << "========================================";
    qDebug() << "=== ЗАПУСК АВТОМАТИЧЕСКИХ ТЕСТЬОВ ===";
    qDebug() << "========================================";

    TestDataHandler testObj;
    int testResult = QTest::qExec(&testObj, argc, argv);

    qDebug() << "========================================";
    qDebug() << "=== ТЕСТЫ ЗАВЕРШЕНЫ С КОДОМ:" << testResult << " ===";
    qDebug() << "========================================";

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
