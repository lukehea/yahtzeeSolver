#include "combinationfinder.h"

combinationFinder::combinationFinder(QVector<QVector<int>> &newCombos, int newElements, int newRank, int startingComboCount){

    elements = newElements;
    combos = newCombos;
    rank = newRank;
    combinationsAvailable = startingComboCount;


    //list of possible combination counts for five elements with samples of size {2,3,4}
    start = elements + rank;

    //factorial lambda
    auto fact = [](const int n){int k = n; for(int i=n-1;i>1;--i){k *= i;} return std::max(k,1);};

    //determines starting position in list for sample size relative to sample size
    for (int i=2;i<(rank+2);++i){
        start += int((fact(elements))/(fact(i)*fact(elements-i)));
    }

    end = start + int((fact(elements))/(fact(rank)*fact(elements-rank)));
    calculateFrom = end + 1;
}

/*void combinationFinder::findCombinations(){
    int pos = start;
    for (int i=end+1;i<std::min(end+10,32);++i){
        for (int j = (i-(end+1));j<(combos[i].size());++j){
            std::copy(combos[i].begin(),combos[i].end(),std::back_inserter(combos[pos]));
            combos[pos].erase(combos[pos].begin()+j);
            pos++;
            emit combinationCompleted();
        }
        combinationsAvailable--;
    }
}*/

void combinationFinder::combinationAvailable(){
    combinationsAvailable++;
    calculateCombinations();
}

void combinationFinder::calculateCombinations(){
    for (int j = (calculateFrom-(end+1));j<(combos[calculateFrom].size());++j){
        std::copy(combos[calculateFrom].begin(),combos[calculateFrom].end(),std::back_inserter(combos[start]));
        combos[start].erase(combos[start].begin()+j);
        start++;
        if (rank>0) emit combinationCompleted();
    }
    calculateFrom++;
    combinationsAvailable--;
    if (combinationsAvailable > 0) calculateCombinations();
}

void combinationFinder::connectCombinationsFinders(combinationFinder back){
    QObject::connect(this, SIGNAL(combinationFinder::combinationCompleted()), &back, SLOT(combinationFinder::combinationCompleted()));
}
