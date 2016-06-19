#include "dialog.h"
#include "ui_dialog.h"
#include <mainwindow.h>

extern Ui::MainWindow *ui;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui2(new Ui::Dialog)
{
    ui2->setupUi(this);
    ui2->labelScore->setText(QString::number(Score::finalScore));
}

Dialog::~Dialog()
{
    delete ui2;
}

void Dialog::on_pushButton_clicked()
{
    emit restartGame();
    this->close();
}

void Dialog::on_pushButton_2_clicked()
{
    emit quitGame();
    this->close();
}
