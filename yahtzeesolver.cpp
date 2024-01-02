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
    imageHandles = {":/icons/diceBackground.png",":/icons/diceOne.png",":/icons/diceTwo.png",":/icons/diceThree.png",":/icons/diceFour.png",":/icons/diceFive.png",":/icons/diceSix.png"};
    diceImages = QVector<QPixmap>(5);
    for (int i = 0;i<5;++i){
        diceImages[i] = QPixmap(imageHandles[0]);
    }
    exValue = 0;
}

yahtzeeSolver::~yahtzeeSolver()
{
    delete ui;
}


void yahtzeeSolver::testDiceValues()
{
    QVector<int> keptDice = testRolls(dice, rolls);
    for (int i = 0;i<5;i++){
        dice[i] = keptDice[i];
        diceImages[i] = imageHandles[dice[i]];
    }
    exValue = keptDice[5];
}

void yahtzeeSolver::updateExLabel(){
    ui->exLabel->setText(QString::number(exValue));
}

void yahtzeeSolver::updateRollLabel(){
    ui->rollLabel->setText(QString::number(rolls));
}

