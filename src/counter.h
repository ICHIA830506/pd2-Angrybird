#ifndef COUNTER_H
#define COUNTER_H

#include <QGraphicsTextItem>

class Counter : public QGraphicsTextItem{

public:
    Counter(QGraphicsItem * parent = 0);

    void decrease();


    static int counter;
};

#endif // COUNTER_H
