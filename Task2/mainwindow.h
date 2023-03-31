#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "addelement.h"
#include "ui_addelement.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_addNewElements_clicked();

    void on_pushButton_showMatrices_clicked();

public:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
