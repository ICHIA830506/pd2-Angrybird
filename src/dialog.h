#ifndef DIALOG_H
#define DIALOG_H


#include <QDialog>
#include "score.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

signals:

    void restartGame();
    void quitGame();



private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Dialog *ui2;




};

#endif // DIALOG_H
