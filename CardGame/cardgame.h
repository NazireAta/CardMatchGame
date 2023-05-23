#ifndef CARDGAME_H
#define CARDGAME_H
#include <QAbstractButton>
#include <iostream>
#include <QMainWindow>
using namespace std;

namespace Ui { class CardGame; }


class CardGame : public QMainWindow
{
    Q_OBJECT

public:
    explicit CardGame(QWidget *parent = nullptr);
    ~CardGame();
    vector<QString> animals{"cat","cat","cow","cow","dog","dog","cobra","cobra","butterfly","butterfly","eagle","eagle","camel","camel","crow","crow","tortoise","tortoise","frog","frog","scorpion","scorpion","pigeon","pigeon","fish", "fish", "tiger", "tiger", "horse", "horse"};
    bool pause = false;
    bool isSecond = false;
    int score = 0;
    int tries = 50;
    QAbstractButton* firstButton; //previousButton
    QAbstractButton* secondButton;
    map<QAbstractButton *, QString> buttonsList;
    void shuffle();

private:
    Ui::CardGame *ui;

private slots:
    void newGame();
    void move(int);
};
#endif // CARDGAME_H
