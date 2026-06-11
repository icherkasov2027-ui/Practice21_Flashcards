#include "datahandler.h"
#include <QDebug>

void DataHandler::saveDecks(const QList<Deck>& decks, const QString& filename) {
    qDebug() << "Лог: Начало сохранения данных в файл:" << filename;

    QJsonArray deckArray;
    for (const auto& deck : decks) {
        QJsonObject deckObj;
        deckObj["title"] = deck.title;
        QJsonArray cardArray;
        for (const auto& card : deck.cards) {
            QJsonObject cardObj;
            cardObj["front"] = card.front;
            cardObj["back"] = card.back;
            cardObj["difficulty"] = card.difficulty;
            cardArray.append(cardObj);
        }
        deckObj["cards"] = cardArray;
        deckArray.append(deckObj);
    }
    QJsonObject root;
    root["decks"] = deckArray;

    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(root).toJson());
        file.close();
        qDebug() << "Лог: Успешно сохранено наборів:" << decks.size();
    } else {
        qCritical() << "КРИТИЧЕСКАЯ ОШИБКА: Не удалось открыть файл для записи:" << filename;
    }
}

QList<Deck> DataHandler::loadDecks(const QString& filename) {
    qDebug() << "Лог: Попытка загрузить данные из файла:" << filename;

    QList<Deck> decks;
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Предупреждение: Файл не найден, возвращаем пустой список. Файл:" << filename;
        return decks;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray deckArray = doc.object()["decks"].toArray();
    for (const auto& deckVal : deckArray) {
        QJsonObject deckObj = deckVal.toObject();
        Deck deck;
        deck.title = deckObj["title"].toString();
        QJsonArray cardArray = deckObj["cards"].toArray();
        for (const auto& cardVal : cardArray) {
            QJsonObject cardObj = cardVal.toObject();
            deck.cards.append({cardObj["front"].toString(), cardObj["back"].toString(), cardObj["difficulty"].toInt()});
        }
        decks.append(deck);
    }

    qDebug() << "Лог: Успешно загружено наборів из файла:" << decks.size();
    return decks;
}
