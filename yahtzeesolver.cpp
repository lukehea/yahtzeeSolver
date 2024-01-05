#include "yahtzeesolver.h"
#include "./ui_yahtzeesolver.h"

QString upArrowHandle = "<:\\icons\\buttons\\upArrow>";
QString downArrowHandle = "<:\\icons\\buttons\\downArrow>";
QVector<QString> imageHandles = {":\\icons\\dice\\diceBackground.png",":\\icons\\dice\\diceOne.png",":\\icons\\dice\\diceTwo.png",":\\icons\\dice\\diceThree.png",":\\icons\\dice\\diceFour.png",":\\icons\\dice\\diceFive.png",":\\icons\\dice\\diceSix.png"};

yahtzeeSolver::yahtzeeSolver(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::yahtzeeSolver)
{
    ui->setupUi(this);
    //QPushButton *upDiceOne = new QPushButton();
    ui->upDice->setIcon(QPixmap(upArrowHandle));
    connect(ui->lockIn, &QPushButton::clicked, this, &yahtzeeSolver::testDiceValues);

    activeDie = QVector<dice*>(0);
    for (int i = 0;i<5;++i){
        QPushButton* up = new QPushButton();
        QPushButton* down = new QPushButton();
        up->setParent(ui->frame);
        up->setParent(ui);
        activeDie.append(new dice());
        connect(ui->up, &QPushButton::clicked, &activeDie[i], &dice::increase);
        connect(ui->down, &QPushButton::clicked, &activeDie[i], &dice::decrease);
    }
    exValue = 0;
    rolls = 3;
}

yahtzeeSolver::~yahtzeeSolver()
{
    delete ui;
    delete &activeDie;
    delete &rolls;
    delete &exValue;
}

void yahtzeeSolver::testDiceValues()
{
    //prevents dice checking if any die haven't been set
    if (!isValidRoll()) return;

    //gets die to keep and expected value
    if (rolls>0){
        QVector<int> dice(5);
        for (int i = 0;i<5;i++){
            dice[i] = activeDie[i]->value;
        }
        QVector<int> keptDice = testRolls(dice, rolls);
        rolls--;
        for (int i = 0;i<5;i++){
            activeDie[i]->value = keptDice[i];
            activeDie[i]->updateImg();
        }
        exValue = keptDice[5];
    }else{
        rolls = 3;
        for (int i = 0;i<5;i++){
            activeDie[i]->value = i+1; //change to 0
            activeDie[i]->updateImg();
        }
        exValue = 0;
    }
    ui->exLabel->setText(QString::number(exValue));
    ui->rollLabel->setText(QString::number(rolls));
}

bool yahtzeeSolver::isValidRoll(){
    for (int i = 0;i<5;++i){
        if (activeDie[i]->value == 0) return false;
    }
    return true;
}

dice::dice(QObject *parent)
: QObject{parent}
{
    value = 0;
    diceDisplayed = new QImage(imageHandles[0]);
    //diceDisplayed->setParent(parent);
}

dice::~dice(){
    delete diceDisplayed;
    delete &value;
}

void dice::increase(){
    value++;
    this->updateImg();
}

void dice::decrease(){
    value--;
    this->updateImg();
}

void dice::updateImg(){
    //change this ASAP
    diceDisplayed = new QImage(imageHandles[value]);
}
