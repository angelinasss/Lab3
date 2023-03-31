#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "../../Documents/vector/vector.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_2->hide();
    ui->label_4->hide();
    ui->pushButton_saveNewCapacity->hide();
    ui->lineEdit_3->hide();
    ui->lineEdit_4->hide();
    ui->label_5->hide();
    ui->label_6->hide();
    ui->pushButton_saveNewSize->hide();
    ui->pushButton_SaveData1->hide();
    ui->label_7->hide();
    ui->pushButton_saveSwapindeces->hide();
    ui->label_8->hide();
    ui->pushButton_saveEraseIndex->hide();
    ui->label_9->hide();
    ui->pushButton->hide();
    ui->label_10->hide();
    ui->label_11->hide();
    ui->label_12->hide();
    ui->label_13->hide();
    ui->pushButton_2->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

Vector<int> myVector;

void inputData(QString vectorStr) {
    int counter = 0;
    QString tmp;
    for(int i = 0; i < vectorStr.size(); i++) {
        if(vectorStr[i] == ' ') {
            if(counter == 0) {
            myVector.push_back(stoi(tmp.toStdString()));
            }
            tmp.clear();
            counter++;
        }
        else {
            tmp += vectorStr[i];
            counter = 0;
        }
    }
}

void inputData1(QString vectorStr) {
    int counter = 0;
    QString tmp;
    for(int i = 0; i < vectorStr.size(); i++) {
        if(vectorStr[i] == ' ') {
            if(counter == 0) {
            myVector.emplace_back(stoi(tmp.toStdString()));
            }
            tmp.clear();
            counter++;
        }
        else {
            tmp += vectorStr[i];
            counter = 0;
        }
    }
}

void MainWindow::on_pushButton_saveData_clicked()
{
    myVector.clear();
    QString myVectorStr = ui->lineEdit->text().trimmed() + " ";
    try {

    inputData(myVectorStr);

    ui->lineEdit->clear();
    ui->textBrowser->clear();

    myVectorStr.clear();
    for(int i = 0; i < myVector.size(); i++) {
        myVectorStr += QString::number(*(myVector.begin() + i)) + " ";
    }

    ui->textBrowser->append(myVectorStr);

    } catch(...) {
        QMessageBox::critical(this, "ERROR!", "Данные введены неверно!\nПовторите ввод!");
    }
}


void MainWindow::on_pushButton_empty_clicked()
{
    bool check = myVector.empty();
    if(check) {
        QMessageBox::information(this, "Info about vector", "Vector is empty!");
    }
    else {
        QMessageBox::information(this, "Info about vector", "Vector isn't empty!");
    }
}


void MainWindow::on_pushButton_size_clicked()
{
    QString sizeVector = QString::number(myVector.size());
    QMessageBox::information(this, "Info about vector", "Vector size: " + sizeVector);
}


void MainWindow::on_pushButton_capacity_clicked()
{
    QString capacityVector = QString::number(myVector.capacity());
    QMessageBox::information(this, "Info about vector", "Vector capacity: " + capacityVector);
}


void MainWindow::on_pushButton_max_size_clicked()
{
    QString vectorMaxSize = QString::number(myVector.max_size());
    QMessageBox::information(this, "Info about vector", "Vector max size: " + vectorMaxSize);
}


void MainWindow::on_pushButton_pop_back_clicked()
{
    if(!myVector.empty()) {
    myVector.pop_back();
    ui->textBrowser->clear();
    QString myVectorStr;
    for(int i = 0; i < myVector.size(); i++) {
        myVectorStr += QString::number(myVector[i]) + " ";
    }

    ui->textBrowser->append(myVectorStr);

    QMessageBox::information(this, "Info about vector", "The last element of the vector was successfully removed!");
    }
    else {
        QMessageBox::critical(this, "Info about vector", "The vector is empty!\nFill in the vector and repeat the action!");
    }
}


void MainWindow::on_pushButton_reserve_clicked()
{
    ui->pushButton_saveData->hide();
    ui->label->hide();
    ui->label_3->hide();
    ui->textBrowser->hide();
    ui->lineEdit->hide();
    ui->lineEdit_2->show();
    ui->label_4->show();
    ui->pushButton_saveNewCapacity->show();
}


void MainWindow::on_pushButton_saveNewCapacity_clicked()
{
    try {

    int newCapacity = stoi(ui->lineEdit_2->text().trimmed().toStdString());

    myVector.reserve(newCapacity);

    QMessageBox::information(this, "Info about vector", "The vector capacity was successfully changed!");

    ui->lineEdit_2->hide();
    ui->label_4->hide();
    ui->pushButton_saveNewCapacity->hide();
    ui->pushButton_saveData->show();
    ui->label->show();
    ui->label_3->show();
    ui->textBrowser->show();
    ui->lineEdit->show();

    } catch(...) {
        QMessageBox::critical(this, "ERROR!", "Данные введены неверно!\nПовторите ввод!");
    }
}


void MainWindow::on_pushButton_resize_clicked()
{
    if(!myVector.empty()) {
    ui->pushButton_saveData->hide();
    ui->label->hide();
    ui->label_3->hide();
    ui->textBrowser->hide();
    ui->lineEdit->hide();
    ui->lineEdit_3->show();
    ui->lineEdit_4->show();
    ui->label_5->show();
    ui->label_6->show();
    ui->pushButton_saveNewSize->show();
    }
    else {
       QMessageBox::critical(this, "Info about vector", "The vector is empty!\nFill in the vector and repeat the action!");
    }
}


void MainWindow::on_pushButton_saveNewSize_clicked()
{
    try {
    size_t newSize = stoi(ui->lineEdit_3->text().trimmed().toStdString());
    int newElement = stoi(ui->lineEdit_4->text().trimmed().toStdString());

    myVector.resize(newSize, newElement);

    ui->textBrowser->clear();

    QString myVectorStr;
    for(int i = 0; i < myVector.size(); i++) {
        myVectorStr += QString::number(myVector[i]) + " ";
    }

    ui->textBrowser->append(myVectorStr);

    QMessageBox::information(this, "Info about vector", "The vector size was successfully changed!");

    ui->pushButton_saveData->show();
    ui->lineEdit_4->clear();
    ui->label->show();
    ui->label_3->show();
    ui->textBrowser->show();
    ui->lineEdit_3->hide();
    ui->lineEdit_4->hide();
    ui->lineEdit->show();
    ui->label_5->hide();
    ui->label_6->hide();
    ui->pushButton_saveNewSize->hide();
    }
    catch(...) {
        QMessageBox::critical(this, "ERROR!", "Данные введены неверно!\nПовторите ввод!");
    }
}

void MainWindow::on_pushButton_emplace_back_clicked()
{   
    ui->pushButton_saveData->hide();
    ui->label->hide();
    ui->label_3->hide();
    ui->textBrowser->hide();
    ui->lineEdit->hide();
    ui->lineEdit_4->show();
    ui->label_6->show();
    ui->pushButton_SaveData1->show();
}
void MainWindow::on_pushButton_SaveData1_clicked()
{
    QString myVectorStr = ui->lineEdit_4->text().trimmed() + " ";
    try {

    inputData1(myVectorStr);

    myVectorStr.clear();
    for(int i = 0; i < myVector.size(); i++) {
        myVectorStr += QString::number(*(myVector.begin() + i)) + " ";
    }

    ui->textBrowser->clear();

    ui->textBrowser->append(myVectorStr);
    ui->lineEdit_4->clear();
    ui->pushButton_saveData->show();
    ui->label->show();
    ui->label_3->show();
    ui->textBrowser->show();
    ui->lineEdit->show();
    ui->lineEdit_4->hide();
    ui->label_6->hide();
    ui->pushButton_SaveData1->hide();

    } catch(...) {
        QMessageBox::critical(this, "ERROR!", "Данные введены неверно!\nПовторите ввод!");
    }
}


void MainWindow::on_pushButton_swap_clicked()
{
    if(!myVector.empty()) {
    ui->pushButton_saveData->hide();
    ui->label->hide();
    ui->label_3->hide();
    ui->label_7->show();
    ui->pushButton_saveSwapindeces->show();
    }
    else {
        QMessageBox::critical(this, "Info about vector", "The vector is empty!\nFill in the vector and repeat the action!");
    }
}


void MainWindow::on_pushButton_saveSwapindeces_clicked()
{
    Vector<int> newVector;
    QString swapVector = ui->lineEdit->text().trimmed() + " ";
    try {
        int counter = 0;
        QString tmp;
        for(int i = 0; i < swapVector.size(); i++) {
            if(swapVector[i] == ' ') {
                if(counter == 0) {
                newVector.push_back(stoi(tmp.toStdString()));
                }
                tmp.clear();
                counter++;
            }
            else {
                tmp += swapVector[i];
                counter = 0;
            }
        }
    ui->textBrowser->clear();

    swapVector.clear();

    newVector.swap(myVector);

    QString myVectorstr;
    for(int i = 0; i < newVector.size(); i++) {
        swapVector += QString::number(*(newVector.begin() + i)) + " ";
    }
    for(int i = 0; i < myVector.size(); i++) {
        myVectorstr += QString::number(*(myVector.begin() + i)) + " ";
    }

    ui->textBrowser->append("The first vector:");
    ui->textBrowser->append(myVectorstr);
    ui->textBrowser->append("New(swap) vector:");
    ui->textBrowser->append(swapVector);

    ui->pushButton_saveData->show();
    ui->label->show();
    ui->label_3->show();
    ui->label_7->hide();
    ui->pushButton_saveSwapindeces->hide();
    ui->lineEdit->clear();
    ui->lineEdit_4->clear();
    ui->pushButton_saveData->show();
    ui->label->show();
    ui->label_3->show();
    ui->textBrowser->show();
    ui->lineEdit->show();
    ui->lineEdit_4->hide();
    ui->label_6->hide();
    ui->pushButton_SaveData1->hide();
    ui->label_7->hide();
    ui->pushButton_saveSwapindeces->hide();

    } catch(...) {
        QMessageBox::critical(this, "ERROR!", "Данные введены неверно!\nПовторите ввод!");
    }
}


void MainWindow::on_pushButton_erase_clicked()
{
    if(!myVector.empty()) {
    ui->pushButton_saveData->hide();
    ui->label->hide();
    ui->label_8->show();
    ui->pushButton_saveEraseIndex->show();
    }
    else {
        QMessageBox::critical(this, "Info about vector", "The vector is empty!\nFill in the vector and repeat the action!");
    }
}


void MainWindow::on_pushButton_saveEraseIndex_clicked()
{
    try {

    int eraseIndex = stoi(ui->lineEdit->text().trimmed().toStdString());

    if(eraseIndex >= myVector.size()) {
        QMessageBox::critical(this, "ERROR!", "Данные введены неверно!\nПовторите ввод!");
    }
    auto it = myVector.begin() + eraseIndex - 1;
    myVector.erase(it);

    ui->lineEdit->clear();
    ui->textBrowser->clear();

    QString changedVector;
    for(int i = 0; i < myVector.size(); i++) {
        changedVector += QString::number(*(myVector.begin() + i)) + " ";
    }

    ui->textBrowser->append(changedVector);

    ui->pushButton_saveData->show();
    ui->label->show();
    ui->label_8->hide();
    ui->pushButton_saveEraseIndex->hide();

    } catch(...) {
        QMessageBox::critical(this, "ERROR!", "Данные введены неверно!\nПовторите ввод!");
    }
}


void MainWindow::on_pushButton_insert_clicked()
{
    ui->pushButton_saveData->hide();
    ui->label->hide();
    ui->label_9->show();
    ui->pushButton->show();
    ui->lineEdit_3->show();
    ui->lineEdit_4->show();
    ui->lineEdit->hide();
    ui->textBrowser->hide();
    ui->label_3->hide();
    ui->label_10->show();
    ui->label_11->show();
}


void MainWindow::on_pushButton_clicked()
{
    try {

    int insertIndex = stoi(ui->lineEdit_3->text().trimmed().toStdString());
    int newElement = stoi(ui->lineEdit_4->text().trimmed().toStdString());

    if(insertIndex >= myVector.size()) {
        QMessageBox::critical(this, "ERROR!", "Данные введены неверно!\nПовторите ввод!");
    }
    else {
    auto it = myVector.begin() + insertIndex - 1;
    myVector.insert(it, newElement);

    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->textBrowser->clear();

    QString changedVector;
    for(int i = 0; i < myVector.size(); i++) {
        changedVector += QString::number(*(myVector.begin() + i)) + " ";
    }

    ui->textBrowser->append(changedVector);

    ui->pushButton_saveData->show();
    ui->label->show();
    ui->lineEdit->show();
    ui->textBrowser->show();
    ui->label_3->show();
    ui->label_9->hide();
    ui->pushButton->hide();
    ui->lineEdit_3->hide();
    ui->lineEdit_4->hide();
    ui->label_10->hide();
    ui->label_11->hide();
    }
    } catch(...) {
        QMessageBox::critical(this, "ERROR!", "Данные введены неверно!\nПовторите ввод!");
    }
}

void MainWindow::on_pushButton_assign_clicked()
{
    ui->label_12->show();
    ui->label_13->show();
    ui->pushButton_saveData->hide();
    ui->label->hide();
    ui->lineEdit_3->show();
    ui->lineEdit_4->show();
    ui->lineEdit->hide();
    ui->textBrowser->hide();
    ui->label_3->hide();
    ui->pushButton_2->show();
}


void MainWindow::on_pushButton_2_clicked()
{
    try {

    size_t amountEl = stoi(ui->lineEdit_3->text().trimmed().toStdString());
    const int newElement = stoi(ui->lineEdit_4->text().trimmed().toStdString());

    myVector.assign(amountEl, newElement);

    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->textBrowser->clear();

    QString changedVector;
    for(int i = 0; i < myVector.size(); i++) {
        changedVector += QString::number(*(myVector.begin() + i)) + " ";
    }

    ui->textBrowser->append(changedVector);

    ui->label_12->hide();
    ui->label_13->hide();
    ui->pushButton_saveData->show();
    ui->label->show();
    ui->lineEdit_3->hide();
    ui->lineEdit_4->hide();
    ui->lineEdit->show();
    ui->textBrowser->show();
    ui->label_3->show();
    ui->pushButton_2->hide();
    } catch(...) {
        QMessageBox::critical(this, "ERROR!", "Данные введены неверно!\nПовторите ввод!");
    }
}

