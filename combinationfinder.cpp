#include "combinationfinder.h"

//factorial lambda
auto fact = [](const int n){int k = n; for(int i=n-1;i>1;--i){k *= i;} return std::max(k,1);};

QVector<QVector<int>*> findAllCombinations(QVector<int>* elements){

    int eltCount = elements->size();

    //auto fact = [](const int n){int k = n; for(int i=n-1;i>1;--i){k *= i;} return std::max(k,1);};
    QVector<QVector<int>*> combos(0);
    for (int i = 1;i<=31;++i){
        combos.push_back(new QVector<int>(0));
    }

    for (int i=0;i<eltCount;i++){
        combos[i]->push_back(elements->at(i));
    }
    combos[combos.size()-1] = elements;


    QVector<combinationFinder*> finders(0);
    for (int i = 2;i<eltCount;++i){
        finders.push_back(new combinationFinder(&combos, eltCount, i));
        if (i>2)finders[i-2]->connectCombinationsFinders(*finders[i-3]);
    }
    finders[finders.size()-1]->activate();

    return combos;
}

combinationFinder::combinationFinder(QVector<QVector<int>*>* newCombos, int newElements, int smpSize, QObject *parent)
: QObject{parent}
{

    elements = newElements;
    combos = newCombos;
    sample = smpSize;

    skipValues = new QVector<int>(0);


    //list of possible combination counts for five elements with samples of size {2,3,4}
    insertionPoint = elements;

    //determines starting position in list for sample size relative to sample size
    for (int i=2;i<(sample);++i){
        insertionPoint += int((fact(elements))/(fact(i)*fact(elements-i)));
    }

    calculateFrom = insertionPoint + int((fact(elements))/(fact(sample)*fact(elements-sample)));
    lastAvailable = calculateFrom - 1;

    inactive = true;

    QObject::connect(this, &combinationFinder::activateSelf, this, &combinationFinder::combinationAvailable);
}

combinationFinder::~combinationFinder()
{
    delete skipValues;
    delete &elements;
    delete &insertionPoint;
    delete &calculateFrom;
    delete &lastAvailable;
    delete &sample;
    delete &inactive;
}

void combinationFinder::activate(){
    emit activateSelf();
}

void combinationFinder::combinationAvailable(int skipFirst){
    lastAvailable++;
    skipValues->push_back(skipFirst);
    //this might cause problems w/ parallelism
    if (inactive){
        inactive = false;
        calculateCombinations();
    }
}

void combinationFinder::calculateCombinations(){

    for (int j = skipValues->at(0);j<combos->at(calculateFrom)->size();j++){
        //copies combos at calculation point into combos at insertion point
        for (int i = 0;i<combos->at(calculateFrom)->size();i++){
            combos->at(insertionPoint)->push_back(combos->at(calculateFrom)->at(i));
        }
        //deletes element j from copied vector and increments to next insertion point
        combos->at(insertionPoint)->erase(combos->at(insertionPoint)->begin()+j);
        insertionPoint++;
        //if not calculating smallest possible combinations, signal next thread down to begin working w/ new combination
        if (sample>2) emit combinationCompleted(j);
    }
    skipValues->removeFirst();
    //increments to next calculation point to begin
    calculateFrom++;
    //this wont work, need to rework before implementing parallelism
    if (calculateFrom <= lastAvailable) {
        calculateCombinations();
    }else inactive = true;
}

void combinationFinder::connectCombinationsFinders(combinationFinder& back){
    QObject::connect(this, &combinationFinder::combinationCompleted, &back, &combinationFinder::combinationAvailable);
}
