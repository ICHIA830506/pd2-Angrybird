#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

class Score: public QGraphicsTextItem{

public:
    Score(QGraphicsItem * parent = 0);
    void increase();
    static int finalScore;
    static void setFinalScore(int score);
    int getScore() const;

private:
    int score;


};

#endif // SCORE_H
