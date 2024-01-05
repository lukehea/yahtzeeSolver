#ifndef YAHTZEESOLVER_H
#define YAHTZEESOLVER_H

#include <QMainWindow>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <QSemaphore>
#include <QString>
#include <QVector>
#include <QIcon>
#include "combinationfinder.h"
#include "dice.h"

QVector<int> testRolls(QVector<int> rolled, int rolls);
void cleanDuplicates(QVector<QVector<int>*> *combos, QVector<int> *toRemove, int start, int end);
int getExValue(QVector<int> held, int rolls);

QT_BEGIN_NAMESPACE
namespace Ui { class yahtzeeSolver; }
QT_END_NAMESPACE

class yahtzeeSolver : public QMainWindow
{
    Q_OBJECT

public:
    yahtzeeSolver(QWidget *parent = nullptr);
    ~yahtzeeSolver();

private slots:
    void testDiceValues();

private:
    void updateDiceImgs();
    bool isValidRoll();

    Ui::yahtzeeSolver *ui;
    QVector<dice*> activeDie;
    int rolls;
    int exValue;
};

#endif // YAHTZEESOLVER_H
