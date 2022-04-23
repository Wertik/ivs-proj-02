#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Manually connect buttons that append to expression.

    vector<QPushButton*> buttons = {
        ui->pushButton_0,
        ui->pushButton_1,
        ui->pushButton_2,
        ui->pushButton_3,
        ui->pushButton_4,
        ui->pushButton_5,
        ui->pushButton_6,
        ui->pushButton_7,
        ui->pushButton_8,
        ui->pushButton_9,
        ui->pushButton_comma,
        ui->pushButton_plus,
        ui->pushButton_minus,
        ui->pushButton_multiply,
        ui->pushButton_divide,
        ui->pushButton_power,
        ui->pushButton_square,
        ui->pushButton_fakt,
        ui->pushButton_l_bracket,
        ui->pushButton_r_bracket
    };

    for (const QPushButton* button : buttons) {
        connect(button, SIGNAL(released()), this, SLOT(press_button()));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::press_button()
{
    QPushButton * button = (QPushButton*)sender();

    QString labelStr;
    if (this->empty) {
        labelStr = button->text();
        this->empty = false;
    } else {
        labelStr = ui->label->text() + button->text();
    }

    ui->label->setText(labelStr);
}

void MainWindow::on_pushButton_clear_released()
{
    ui->label->setText("0");
    this->empty = true;
}

void MainWindow::on_pushButton_equal_released()
{
    // Evaluate expression and display result here.
}

