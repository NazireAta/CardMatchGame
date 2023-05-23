#include "cardgame.h"
#include "./ui_cardgame.h"
#include <QPushButton>
#include <QDebug>
#include <QAbstractButton>
#include <iostream>
#include <map>
#include <QTest>
#include <QMessageBox>
#include <QTimer>
using namespace std;

CardGame::CardGame(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CardGame)
{
    ui->setupUi(this);
    shuffle();
    //if any button is cliked from the buttongroup go to move() slot
    connect(ui->buttonGroup,&QButtonGroup::idClicked, this, &CardGame::move);
    //if newGame button is clicked go to reset() slot
    connect(ui->newGame,SIGNAL(pressed()),this,SLOT(newGame()));
}

CardGame::~CardGame()
{
    delete ui;
}

void CardGame::move(int num){
    if(pause){ // prevents the user from pressing more buttons when already two of them is open
        return;
    }
    if(!(this->isSecond)){ // if there are currently no cards open
        firstButton = ui->buttonGroup->button(num);
        QString firstLabel =QString(buttonsList[firstButton]); //label is the name of the animal hidden under the pressed button
        firstButton->setText(firstLabel); // set the buttons text to label
        firstButton->setEnabled(false); // make pressed one disabled
        isSecond = true; // now there is an open card.
        tries--; //decrement remaining tries
        ui->lcdNumber->display(tries);
    }
    else{
        secondButton = ui->buttonGroup->button(num);
        QString secondLabel =QString(buttonsList[secondButton]); //label is the name of the animal hidden under the pressed button
        secondButton->setText(secondLabel);
        secondButton->setEnabled(false);
        pause = true; // do not let the user to press more buttons if there are currently two of them open
        QTest::qWait(1000); // let the user see the open cards
        pause = false;
        isSecond = false; // we will close the cards, so no cards will be open after this block
        if(buttonsList[secondButton]==buttonsList[firstButton]){ // matched the cards
            firstButton->setEnabled(false); // we can no longer click the buttons
            secondButton->setEnabled(false);
            firstButton->setText(""); // empty the button texts
            secondButton->setText("");
            score++; //increment the score
            ui->lcdNumber_2->display(score);
        }
        else { // failed to match, turn the cards over again
            firstButton->setEnabled(true);
            secondButton->setEnabled(true);
            firstButton->setText("?");
            secondButton->setText("?");
        }
        if(tries == 0){ // no tries are left, the game is lost
            QMessageBox msgBox;
            msgBox.setText("Sorry, you have lost. Press New Game to start again.");
            QTimer::singleShot(3000, [&msgBox]() { msgBox.close(); });
            msgBox.exec();
        }
        else if(score == 15){ // all cards are matched, the game is won
            QMessageBox msgBox;
            msgBox.setText("Congratulations! You have won. Press New Game to start again.");
            QTimer::singleShot(3000, [&msgBox]() { msgBox.close(); });
            msgBox.exec();
        }
    }
}

void CardGame::shuffle(){ //randomly assigs animal names to pushbuttons
    random_shuffle(animals.begin(),animals.end());
    buttonsList[ui->pushButton_1] = animals[1];
    buttonsList[ui->pushButton_2] = animals[2];
    buttonsList[ui->pushButton_3] = animals[3];
    buttonsList[ui->pushButton_4] = animals[4];
    buttonsList[ui->pushButton_5] = animals[5];
    buttonsList[ui->pushButton_6] = animals[6];
    buttonsList[ui->pushButton_7] = animals[7];
    buttonsList[ui->pushButton_8] = animals[8];
    buttonsList[ui->pushButton_9] = animals[9];
    buttonsList[ui->pushButton_10] = animals[10];
    buttonsList[ui->pushButton_11] = animals[11];
    buttonsList[ui->pushButton_12] = animals[12];
    buttonsList[ui->pushButton_13] = animals[13];
    buttonsList[ui->pushButton_14] = animals[14];
    buttonsList[ui->pushButton_15] = animals[15];
    buttonsList[ui->pushButton_16] = animals[16];
    buttonsList[ui->pushButton_17] = animals[17];
    buttonsList[ui->pushButton_18] = animals[18];
    buttonsList[ui->pushButton_19] = animals[19];
    buttonsList[ui->pushButton_20] = animals[20];
    buttonsList[ui->pushButton_21] = animals[21];
    buttonsList[ui->pushButton_22] = animals[22];
    buttonsList[ui->pushButton_23] = animals[23];
    buttonsList[ui->pushButton_24] = animals[24];
    buttonsList[ui->pushButton_25] = animals[25];
    buttonsList[ui->pushButton_26] = animals[26];
    buttonsList[ui->pushButton_27] = animals[27];
    buttonsList[ui->pushButton_28] = animals[28];
    buttonsList[ui->pushButton_29] = animals[29];
    buttonsList[ui->pushButton_30] = animals[0];

}

void CardGame::newGame(){ //restart the game again, everything is set back to default
    shuffle();
    isSecond = false;
    tries = 50;
    score = 0;
    ui->lcdNumber_2->display(score);
    ui->lcdNumber->display(tries);
    foreach(QAbstractButton *button, ui->buttonGroup->buttons()) {
        button->setText("?");
        button->setEnabled(true);
    }
}
