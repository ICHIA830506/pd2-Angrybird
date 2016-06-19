#include "counter.h"
#include <iostream>
#include <QFont>

int Counter::counter = 10;


Counter::Counter(QGraphicsItem *parent): QGraphicsTextItem(parent){



    setPlainText(QString("Bird: ") + QString::number(counter));
    setDefaultTextColor(Qt::white);
    setFont(QFont("times",22));
}



void Counter::decrease(){
    --counter;
    setPlainText(QString("Bird: ") + QString::number(counter));

    if (counter==0){

        std::cout << "counter==0 !" << std::endl ;

    }
}
