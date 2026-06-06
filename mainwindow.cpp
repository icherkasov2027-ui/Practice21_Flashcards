#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "datahandler.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Deck testDeck;
    testDeck.title = "Мій перший набір";
    testDeck.cards.append({"Питання", "Відповідь", 1});

    QList<Deck> decks;
    decks.append(testDeck);

    DataHandler::saveDecks(decks, "my_data.json");
}
