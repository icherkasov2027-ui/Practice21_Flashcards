#ifndef TESTDATAHANDLER_H
#define TESTDATAHANDLER_H

#include <QObject>
#include <QtTest>
#include "datahandler.h"

class TestDataHandler : public QObject {
    Q_OBJECT

private slots:
    void testValidDataSaveAndLoad();
    void testEmptyDeckList();
    void testMissingFile();
    void testCorruptJsonFile();
    void testEmptyStringsInData();
};

#endif
