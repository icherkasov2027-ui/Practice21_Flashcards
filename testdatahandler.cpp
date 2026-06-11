#include "testdatahandler.h"
#include <QFile>
#include <QList>

void TestDataHandler::testValidDataSaveAndLoad() {
    QList<Deck> originalDecks;
    Deck deck;
    deck.title = "Test Deck";
    deck.cards.append({"Front", "Back", 1});
    originalDecks.append(deck);

    QString testFile = "test_valid.json";
    DataHandler::saveDecks(originalDecks, testFile);

    QList<Deck> loadedDecks = DataHandler::loadDecks(testFile);

    QCOMPARE(loadedDecks.size(), 1);
    QCOMPARE(loadedDecks[0].title, QString("Test Deck"));
    QCOMPARE(loadedDecks[0].cards.size(), 1);
    QCOMPARE(loadedDecks[0].cards[0].front, QString("Front"));

    QFile::remove(testFile);
}

void TestDataHandler::testEmptyDeckList() {
    QList<Deck> emptyDecks;
    QString testFile = "test_empty.json";

    DataHandler::saveDecks(emptyDecks, testFile);
    QList<Deck> loadedDecks = DataHandler::loadDecks(testFile);

    QVERIFY(loadedDecks.isEmpty());

    QFile::remove(testFile);
}

void TestDataHandler::testMissingFile() {
    QList<Deck> loadedDecks = DataHandler::loadDecks("non_existent_file_12345.json");

    QVERIFY(loadedDecks.isEmpty());
}

void TestDataHandler::testCorruptJsonFile() {
    QString testFile = "test_corrupt.json";
    QFile file(testFile);
    if (file.open(QIODevice::WriteOnly)) {
        file.write("{ зламаний текст JSON, немає дужок [ ");
        file.close();
    }

    QList<Deck> loadedDecks = DataHandler::loadDecks(testFile);

    QVERIFY(loadedDecks.isEmpty());

    QFile::remove(testFile);
}

void TestDataHandler::testEmptyStringsInData() {
    QList<Deck> originalDecks;
    Deck deck;
    deck.title = "";
    deck.cards.append({"", "", 0});
    originalDecks.append(deck);

    QString testFile = "test_empty_strings.json";
    DataHandler::saveDecks(originalDecks, testFile);

    QList<Deck> loadedDecks = DataHandler::loadDecks(testFile);

    QCOMPARE(loadedDecks.size(), 1);
    QCOMPARE(loadedDecks[0].title, QString(""));
    QCOMPARE(loadedDecks[0].cards[0].front, QString(""));

    QFile::remove(testFile);
}
