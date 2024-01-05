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

    QVector<int> toRemove(0);

    for (int i = 5;i<combos.size();i++){
        std::sort(combos[i]->begin(),combos[i]->end());
    }

    cleanDuplicates(&combos, &toRemove, 0, 4);
    cleanDuplicates(&combos, &toRemove, 5, 14);
    cleanDuplicates(&combos, &toRemove, 15, 24);
    cleanDuplicates(&combos, &toRemove, 25, 29);

    for (int i = 0;i<toRemove.size();i++){
        combos.remove(toRemove[i]-i);
    }

    /*determine expected value of all possible dice combinations
      expected values are placed in array indexed to position of relevant combination*/
    QVector<int> exValues(combos.size());
    //run on 4 threads
    for (int i=0;i<exValues.size();i++){
        exValues[i] = combos[i]->at(0);//getExValue(combos[i], rolls);
        for (int j = 0;j<combos[i]->size();j++){
            //std::cout<<combos[i][j];
        }
    }

    //find position of highest expected value in list
    int maxPos = 0;
    for (int i=1;i<exValues.size();i++){
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

void cleanDuplicates(QVector<QVector<int>*> *combos, QVector<int> *toRemove, int start, int end){
    //returns true if n and m have identical elements (n and m must be sorted)
    auto isOverlapped = [](const QVector<int>* n, const QVector<int>* m){
        for (int i = 0;i<n->size();i++){if(n->at(i)!=m->at(i))return false;}
        return true;};

    for (int i=start+1;i<=end;i++){
        for (int j=start;j<i;j++){
            if (isOverlapped(combos->at(j), combos->at(i))){
                toRemove->push_back(i);
                break;
            }
        }
    }
}
