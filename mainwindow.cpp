#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cantileverdialog.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList Name;
    setWindowTitle("Cantilver calculator & data base");
    ui->tableWidget->setColumnCount(8);
    Name <<"Condition" <<"Q factor" <<"Frequency [Hz]"<<"Amplitude[V]"<<"Amplification"<<"Swing"<<"Swing(vaccum)"<<"Slew Rate";
    ui->tableWidget->setHorizontalHeaderLabels(Name);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonNormal_clicked()
{
    showNormal();
}

void MainWindow::on_pushButtonFull_clicked()
{
    showFullScreen();
}

void MainWindow::on_pushButtonMax_clicked()
{
    showMaximized();
}

void MainWindow::on_pushButtonExit_clicked()
{
    close();
}

void MainWindow::on_pushButtonAdd_clicked()
{
    int res,row;
    int God;
    double Frequency, Period;
    int Amplitude;
    double Gain;
    double Swing;
    double SwingV;
    QString Sr;
    QString AmplitudeString;
    QString PeriodString;
    QString Condition;
    QString SwingStringV;
    QString SwingString;
    QString GainString;
    QString GodString;
    QString FrequencyString;


    CantileverDialog pd;
    pd.setWindowTitle("Cantilever Database");
    res = pd.exec();
    if (res == QDialog::Rejected)
        return;
    God = pd.God();
    Frequency = pd.Frequency();
    Condition =pd.Condition();
    Amplitude = pd.Amplitude();
    Gain = pd.Gain1()*pd.Gain2()*pd.Gain3();
    Swing = pd.Amplitude()/Gain/10;
    SwingV = Swing*100;
    Period = 1/Frequency;
    SwingStringV = QString::number(SwingV);
    SwingString = QString::number(Swing);
    GainString = QString::number(Gain);
    GodString = QString::number(God);
    FrequencyString = QString::number(Frequency);
    PeriodString = QString::number(Period);
    AmplitudeString = QString::number(Amplitude);
    Sr = AmplitudeString +" / "+ PeriodString;


    ui -> tableWidget -> insertRow(ui ->tableWidget->rowCount());
    row = ui->tableWidget->rowCount() -1;
    ui -> tableWidget -> setItem(row,CONDITION, new QTableWidgetItem(Condition));
    ui -> tableWidget -> setItem(row,GOD, new QTableWidgetItem(GodString));
    ui -> tableWidget -> setItem(row,FREQUENCY, new QTableWidgetItem(FrequencyString));
    ui -> tableWidget -> setItem(row,AMPLITUDE, new QTableWidgetItem(AmplitudeString));
    ui -> tableWidget -> setItem(row,GAIN, new QTableWidgetItem(GainString));
    ui -> tableWidget -> setItem(row,SWING, new QTableWidgetItem(SwingString));
    ui -> tableWidget -> setItem(row,SWINGV, new QTableWidgetItem(SwingStringV));
    ui -> tableWidget -> setItem(row,SR, new QTableWidgetItem(Sr));

    QString path = QFileDialog::getSaveFileName(this,QString("E:/Pliki/Belki/plik.txt"),"",QString("(*.txt);;All Files (*)"));
    if(path.isEmpty())
        return;
    else{
        QFile file(path);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::information(this,"Error",file.errorString());
            return;
        }
        else{
            QDataStream out(&file);
            out.setVersion(QDataStream::Qt_5_11);
            out<<"Condition "+Condition<< "\n" << "Q Factor "+GodString<< "\n" <<"Frequency "+FrequencyString<<" \n ";
            out<<"Amplitude "+AmplitudeString<<"\n"<<"Gain "+GainString<< "\n" <<"Swing "+SwingString<< "\n" <<("Swing in vaccum ")+SwingStringV<<" \n ";
            out<<("Slew rate ")+Sr;
        }
    }

}

