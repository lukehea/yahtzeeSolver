#ifndef COMBINATIONFINDER_H
#define COMBINATIONFINDER_H

#include "yahtzeesolver.h"
#include <QVector>

class combinationFinder : public QObject {
    Q_OBJECT

public:
    combinationFinder();
    combinationFinder(QVector<QVector<int>> &newCombos, const int newElements, const int newRank, const int startingComboCount);
    ~combinationFinder();
    void connectCombinationsFinders(combinationFinder back);
    combinationFinder &operator=(combinationFinder &other);

public slots:
    void combinationAvailable();

signals:
    void combinationCompleted();

private:
    void calculateCombinations();

    QVector<QVector<int>> combos;
    int elements;
    int rank;
    int start;
    int end;
    int combinationsAvailable;
    int calculateFrom;
};

#endif // COMBINATIONFINDER_H
