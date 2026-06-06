#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <QString>
#include <QList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

struct Flashcard {
    QString front;
    QString back;
    int difficulty;
};

struct Deck {
    QString title;
    QList<Flashcard> cards;
};

class DataHandler {
public:
    static void saveDecks(const QList<Deck>& decks, const QString& filename);
    static QList<Deck> loadDecks(const QString& filename);
};

#endif // DATAHANDLER_H
