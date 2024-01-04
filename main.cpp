#include "yahtzeesolver.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    yahtzeeSolver w;
    w.show();
    return a.exec();
}

QVector<int> testRolls(QVector<int> rolled, int rolls){
    /*determines all possible dice combinations of length 2,3 and 4
      modifies list of combinations in place*/
    QVector<QVector<int>*> combos = findAllCombinations(&rolled);

    /*determine expected value of all possible dice combinations
      expected values are placed in array indexed to position of relevant combination*/
    QVector<int> exValues(31);
    //run on 4 threads
    for (int i=0;i<31;i++){
        exValues[i] = combos.at(i)->at(0);//getExValue(combos[i], rolls);
        for (int j = 0;j<combos[i]->size();j++){
            //std::cout<<combos[i][j];
        }
    }

    //find position of highest expected value in list
    int maxPos = 0;
    for (int i=1;i<31;i++){
        if (exValues[i]>exValues[maxPos]) maxPos = i;
    }

    //print out dice combination with highest expected value
    QVector<int> result = *combos[maxPos];
    if (result.size()<5){
        for (int i = result.size();i<5;++i){
            //change to 0
            result.push_back(1);
        }
    }
    result.push_back(exValues[maxPos]);
    return result;
}
