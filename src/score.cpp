#include "score.h"
#include <QFont>

int Score::finalScore = 0;

Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent){
    // initioalize the score to 0
    score = 0;

    //draw the text
    setPlainText(QString("Score: ") + QString::number(score));
    setDefaultTextColor(Qt::white);
    setFont(QFont("times",22));
}

void Score::increase(){
    score++;
    setPlainText(QString("Score: ") + QString::number(score));

}

void Score::setFinalScore(int score)
{
    finalScore = score;
}


int Score::getScore() const
{
    return score;
}
