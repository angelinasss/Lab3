#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_pushButton_saveData_clicked();

    void on_pushButton_empty_clicked();

    void on_pushButton_size_clicked();

    void on_pushButton_capacity_clicked();

    void on_pushButton_max_size_clicked();

    void on_pushButton_pop_back_clicked();

    void on_pushButton_reserve_clicked();

    void on_pushButton_saveNewCapacity_clicked();

    void on_pushButton_resize_clicked();

    void on_pushButton_saveNewSize_clicked();

    void on_pushButton_emplace_back_clicked();

    void on_pushButton_SaveData1_clicked();

    void on_pushButton_swap_clicked();

    void on_pushButton_saveSwapindeces_clicked();

    void on_pushButton_erase_clicked();

    void on_pushButton_saveEraseIndex_clicked();

    void on_pushButton_insert_clicked();

    void on_pushButton_clicked();

    void on_pushButton_assign_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
