#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "../../Documents/vector/vector.h"
#include "pair.cpp"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

Vector<pair<Vector<int>, Vector<pair<int,double>>>> doubleMatrix;
Vector<int> firstMatrix;
Vector<pair<int,double>> secondMatrix;

QString convertToString(const Vector<int>& vec) {
    QString result;
    for (int i = 0; i < vec.size(); ++i) {
        result += QString::number(vec[i]) + " ";
    }
    return result;
}

QString convertToString(const Vector<pair<int, double>>& vec) {
    QString result;
    for (int i = 0; i < vec.size(); ++i) {
        result += QString::number(vec[i].first) + " " + QString::number(vec[i].second) + " ";
    }
    return result;
}

void MainWindow::on_pushButton_addNewElements_clicked()
{
    addElement newWindow;
    this->hide();
    newWindow.setModal(true);
    newWindow.exec();
    this->show();
    ui->textBrowser_matrix1->clear();
    ui->textBrowser_matrix2->clear();
    doubleMatrix.push_back(make_pair(firstMatrix, secondMatrix));
}

void addElement::on_pushButton_saveMatrix1_clicked()
{
    try {
    firstMatrix.push_back(stoi(ui->lineEdit_3->text().toStdString()));
    } catch (...) {
    QMessageBox::critical(this, "ERROR!", "Данные введены неверно!\nПовторите ввод!");
    }
    ui->lineEdit_3->clear();
}

void addElement::on_pushButton_saveMatrix2_clicked()
{
    try {
    secondMatrix.push_back(make_pair(stoi(ui->lineEdit->text().toStdString()), stod(ui->lineEdit_2->text().toStdString())));
    }
    catch (...) {
    QMessageBox::critical(this, "ERROR!", "Данные введены неверно!\nПовторите ввод!");
    }
    ui->lineEdit_2->clear();
    ui->lineEdit->clear();
}

void MainWindow::on_pushButton_showMatrices_clicked()
{
    ui->textBrowser_matrix1->clear();
    ui->textBrowser_matrix2->clear();
    for (int i = 0; i < doubleMatrix.size(); i++) {
    ui->textBrowser_matrix1->append(convertToString(doubleMatrix[i].first));
    ui->textBrowser_matrix2->append(convertToString(doubleMatrix[i].second));
    }
}
