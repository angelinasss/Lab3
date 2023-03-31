#ifndef ADDELEMENT_H
#define ADDELEMENT_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class addElement;
}

class addElement : public QDialog
{
    Q_OBJECT

public:
    explicit addElement(QWidget *parent = nullptr);
    ~addElement();

private slots:
    void on_pushButton_exit_clicked();

    void on_pushButton_saveMatrix1_clicked();

    void on_pushButton_saveMatrix2_clicked();

private:
    Ui::addElement *ui;
};

#endif // ADDELEMENT_H
