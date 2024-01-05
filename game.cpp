#include "game.h"

game::game(QObject *parent)
    : QObject{parent}
{

}

int game::upperSection(){
    int sectionValue = 0;
    int sectionScore = 0;
    for (int i = 0;i<6;i++){
        sectionScore += scores[i];
    }
    for (int i = 0;i<6;i++){
        if(scores[i]>0){
            /*
            get number of i dice
            diceProb = get probability of j = (each succesive # of i dice)
                score = (# of i dice)*i
                potentialValue += (diceProb)*[score + (max(0,min(63-sectionScore,score)))/35]
                if j = 5
                    yahtScore = (scores[11] > 0) ? 100 : 50
                    sectionValue += max(potentialValue, diceProb*yahtScore)
            */
        }
    }
}

int game::straights(){
    int sectionValue = 0;

    //possibility of each following outcome * 30 points
    QVector<QVector<int>> possibleSmall = {{1,2,3,4},{2,3,4,5},{3,4,5,6}};
    //possibility of each following outcome * 50 points
    QVector<QVector<int>> possibleLarge = {{1,2,3,4,5},{2,3,4,5,6}};

}

int game::nOfAKind(){
    int sectionValue = 0;

    /*for each possible dice value i
        n = how many times i appears in combination
        if (n+diceToRoll)<3 return
        3Pos = possibility of getting 3
        sectionValue += 3Pos*((3*i)+7)
        if (n+diceToRoll)>=3
            4Pos = possibility of getting 4
            sectionValue += 4Pos*((4*i)+3.5)
    */

    return sectionValue;

    //for 3 of a kind, add 7 to EV
    //for 4 of a kind, add 3.5 to EV
}

int game::fullHouse(){

}
