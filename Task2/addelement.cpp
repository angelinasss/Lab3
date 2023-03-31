#include "addelement.h"
#include "ui_addelement.h"
#include "vector.cpp"
#include "pair.cpp"
#include <QMessageBox>

extern vector<int> firstMatrix;
extern vector<pair<int, double>> secondMatrix;

addElement::addElement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addElement)
{
    ui->setupUi(this);
    firstMatrix.clear();
    secondMatrix.clear();
}

addElement::~addElement()
{
    delete ui;
}

void addElement::on_pushButton_exit_clicked()
{
    window()->close();
}
