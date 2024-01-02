#include "yahtzeesolver.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    yahtzeeSolver w;

    w.updateExLabel();
    w.updateRollLabel();

    w.show();
    return a.exec();
}

QVector<QVector<int>> findAllCombinations(QVector<int> elements){

    int eltCount = elements.size();

    QVector<QVector<int>> combos(32);
    for (int i=0;i<eltCount;i++){
        QVector<int> v = {elements[i]};
        combos[i] = v;
    }
    combos[combos.size()-1] = elements;


    QVector<combinationFinder> finders(eltCount-2);
    for (int i = 0;i<eltCount-1;++i){
        finders[i] = combinationFinder(combos, eltCount, i, 0);
        if (i>0)finders[i].connectCombinationsFinders(finders[i-1]);
    }
    finders[finders.size()-1] = combinationFinder(combos, eltCount, eltCount-1, 1);
    finders[finders.size()-1].connectCombinationsFinders(finders[finders.size()-2]);
    return combos;
}

QVector<int> testRolls(QVector<int> rolled, int rolls){
    /*determines all possible dice combinations of length 2,3 and 4
      modifies list of combinations in place*/
    QVector<QVector<int>> combos = findAllCombinations(rolled);

    /*determine expected value of all possible dice combinations
      expected values are placed in array indexed to position of relevant combination*/
    QVector<int> exValues(32);
    //run on 4 threads
    for (int i=0;i<32;i++){
        exValues[i] = 1;//getExValue(combos[i], rolls);
        for (int j = 0;i<combos[i].size();++j){
            std::cout<<combos[i][j];
        }
    }

    //find position of highest expected value in list
    int maxPos = exValues[0];
    for (int i=1;i<32;i++){
        maxPos = std::max(maxPos,exValues[i]);
    }

    //print out dice combination with highest expected value
    QVector<int> result = combos[maxPos];
    if (result.size()<5){
        for (int i = result.size();i<5;++i){
            result.append(0);
        }
    }
    result.append(exValues[maxPos]);
    return result;
}

