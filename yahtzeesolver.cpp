#include "yahtzeesolver.h"
#include "./ui_yahtzeesolver.h"

yahtzeeSolver::yahtzeeSolver(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::yahtzeeSolver)
{
    ui->setupUi(this);
    //lockIn = new Q
    connect(ui->lockIn, &QPushButton::clicked, this, &yahtzeeSolver::testDiceValues);

    dice = QVector<int>(5);
    for (int i = 0;i<5;i++){
        dice[i] = i+1;//change to 0
    }
    imageHandles = {":/icons/diceBackground.png",":/icons/diceOne.png",":/icons/diceTwo.png",":/icons/diceThree.png",":/icons/diceFour.png",":/icons/diceFive.png",":/icons/diceSix.png"};
    diceImages = QVector<QPixmap>(5);
    for (int i = 0;i<5;++i){
        diceImages[i] = QPixmap(imageHandles[0]);
    }
    exValue = 0;
    rolls = 3;
}

yahtzeeSolver::~yahtzeeSolver()
{
    delete ui;
}

void yahtzeeSolver::testDiceValues()
{
    //prevents dice checking if any die haven't been set
    if (!isValidRoll()) return;

    //gets die to keep and expected value
    if (rolls>0){
        QVector<int> keptDice = testRolls(dice, rolls);
        rolls--;
        for (int i = 0;i<5;i++){
            dice[i] = keptDice[i];
            diceImages[i] = imageHandles[dice[i]];
        }
        exValue = keptDice[5];
    }else{
        rolls = 3;
        for (int i = 0;i<5;i++){
            dice[i] = i+1; //change to 0
            diceImages[i] = imageHandles[dice[i]];
        }
        exValue = 0;
    }
    ui->exLabel->setText(QString::number(exValue));
    ui->rollLabel->setText(QString::number(rolls));
}

void yahtzeeSolver::updateDiceImgs(){

}

bool yahtzeeSolver::isValidRoll(){
    for (int i = 0;i<5;++i){
        if (dice[i] == 0) return false;
    }
    return true;
}
