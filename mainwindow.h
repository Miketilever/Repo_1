#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSaveFile>

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
    void on_pushButtonNormal_clicked();

    void on_pushButtonFull_clicked();

    void on_pushButtonMax_clicked();

    void on_pushButtonExit_clicked();

    void on_pushButtonAdd_clicked();

    void on_pushButtonSave_clicked();

private:
    Ui::MainWindow *ui;
    enum Column
    {
        CONDITION, GOD , FREQUENCY
    };
};
#endif // MAINWINDOW_H