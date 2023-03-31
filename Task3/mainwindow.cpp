#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "../../Documents/vector/vector.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

Vector<int> sequence;

void inputData(QString sequenceStr) {
    int counter = 0;
    QString tmp;
    for(int i = 0; i < sequenceStr.size(); i++) {
        if(sequenceStr[i] == ' ') {
            if(counter == 0) {
            sequence.push_back(stoi(tmp.toStdString()));
            }
            tmp.clear();
            counter++;
        }
        else {
            tmp += sequenceStr[i];
            counter = 0;
        }
    }
}

Vector<int> getMedianSequence() {
    Vector<int> tmpVector;
    Vector<int> b;
    for(int i = 0; i < sequence.size(); i += 3) {
        tmpVector.clear();
        if(i + 2 > sequence.size() - 1) {
            tmpVector.push_back(sequence[i]);
            tmpVector.push_back(sequence[i + 1]);
            b.push_back((tmpVector[0] + tmpVector[1]) / 2);
        }
        else if(i + 1 > sequence.size() - 1) {
            tmpVector.push_back(sequence[i]);
            b.push_back(tmpVector[0]);
        }
        else {

        int fa = sequence[i], sb = sequence[i + 1], tc = sequence[i + 2];

        if(fa > sb) {
            int tmp = sb;
            sb = fa;
            fa = tmp;
        }
        if(tc < sb) {
            int tmp = tc;
            tc = sb;
            sb = tmp;
        }
        if(fa > sb) {
            int tmp = sb;
            sb = fa;
            fa = tmp;
        }

        tmpVector.push_back(fa);
        tmpVector.push_back(sb);
        tmpVector.push_back(tc);

        b.push_back(tmpVector[1]);
        }
    }
    return b;
}

void MainWindow::on_pushButton_saveData_clicked()
{
    sequence.clear();
    QString sequenceStr = ui->lineEdit->text() + " ";
    try {

    inputData(sequenceStr);

    ui->lineEdit->clear();
    ui->textEdit->clear();

    Vector<int> b;
    b = getMedianSequence();

    QString res;
    for(int i = 0; i < b.size(); i++) {
        res += QString::number(b[i]) + " ";
    }

    ui->textEdit->append(res);

    } catch(...) {
        QMessageBox::critical(this, "ERROR!", "Данные введены неверно!\nПовторите ввод!");
    }
}
