#ifndef YAHTZEESOLVER_H
#define YAHTZEESOLVER_H

#include <QMainWindow>
#include <iterator>
#include <iostream>
#include <QSemaphore>
#include <QString>
#include <QVector>
#include "combinationfinder.h"

QVector<int> testRolls(QVector<int> rolled, int rolls);
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
    QVector<int> dice;
    int rolls;
    int exValue;
    QVector<QString> imageHandles;
    QVector<QPixmap> diceImages;

};
#endif // YAHTZEESOLVER_H
