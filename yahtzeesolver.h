#ifndef YAHTZEESOLVER_H
#define YAHTZEESOLVER_H

#include <QMainWindow>
#include <iterator>
#include <iostream>
#include <QSemaphore>
#include <QString>
#include <QVector>
#include "combinationfinder.h"

QT_BEGIN_NAMESPACE
namespace Ui { class yahtzeeSolver; }
QT_END_NAMESPACE

class yahtzeeSolver : public QMainWindow
{
    Q_OBJECT

public:
    yahtzeeSolver(QWidget *parent = nullptr);
    ~yahtzeeSolver();
    void updateExLabel();
    void updateRollLabel();

private slots:
    void testDiceValues();

private:
    Ui::yahtzeeSolver *ui;
    QVector<int> dice;
    int rolls;
    int exValue;
    QVector<QString> imageHandles;
    QVector<QPixmap> diceImages;

};

QVector<int> testRolls(QVector<int> rolled, int rolls);
int getExValue(QVector<int> held, int rolls);

/*class extendedSemaphore : public QSemaphore{
    Q_OBJECT

public:
    extendedSemaphore& operator=(extendedSemaphore& other);
};*/

#endif // YAHTZEESOLVER_H
