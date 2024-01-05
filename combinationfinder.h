#ifndef COMBINATIONFINDER_H
#define COMBINATIONFINDER_H

#include "yahtzeesolver.h"
#include <QVector>
#include <QtMath>

QVector<QVector<int>*> findAllCombinations(QVector<int> *elements);

class combinationFinder : public QObject {
    Q_OBJECT

public:
    explicit combinationFinder(QVector<QVector<int>*>* newCombos, int newElements, int smpSize, QObject *parent = nullptr);
    ~combinationFinder();
    void connectCombinationsFinders(combinationFinder& back);
    void activate();

public slots:
    void combinationAvailable(int skipFirst);

signals:
    void activateSelf(int skipFirst = 0);
    void combinationCompleted(int skipFirst);

private:
    void calculateCombinations();

    QVector<QVector<int>*>* combos;
    QVector<int>* skipValues;
    int elements;
    int sample;
    int insertionPoint;
    int calculateFrom;
    int lastAvailable;
    bool inactive;
};

#endif // COMBINATIONFINDER_H
