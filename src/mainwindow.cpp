#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_0, SIGNAL(released()),this,SLOT(press_button())); //push buttons for every number
    connect(ui->pushButton_1, SIGNAL(released()),this,SLOT(press_button()));
    connect(ui->pushButton_2, SIGNAL(released()),this,SLOT(press_button()));
    connect(ui->pushButton_3, SIGNAL(released()),this,SLOT(press_button()));
    connect(ui->pushButton_4, SIGNAL(released()),this,SLOT(press_button()));
    connect(ui->pushButton_5, SIGNAL(released()),this,SLOT(press_button()));
    connect(ui->pushButton_6, SIGNAL(released()),this,SLOT(press_button()));
    connect(ui->pushButton_7, SIGNAL(released()),this,SLOT(press_button()));
    connect(ui->pushButton_8, SIGNAL(released()),this,SLOT(press_button()));
    connect(ui->pushButton_9, SIGNAL(released()),this,SLOT(press_button()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::press_button()
{
    //qDebug() << "test";
    QPushButton * button = (QPushButton*)sender(); // signal that sends number to calculator

    double label_num; // store number
    QString label_str; // string from number

    label_num = (ui->label->text() + button->text()).toDouble(); // double convertion

    label_str = QString::number(label_num,'g',16); // converting to string and limit maximum numbers which can be desplayed to 16

    ui->label->setText(label_str); // sending to output
}

void MainWindow::on_pushButton_clear_released()
{
    ui->label->setText("0");
}


void MainWindow::on_pushButton_comma_released()
{
    ui->label->setText(ui->label->text() + ".");
}

