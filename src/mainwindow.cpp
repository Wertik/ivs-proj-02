#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QShortcut>
#include <QClipboard>
#include <QMessageBox>

using namespace std;

#define STYLE_DISPLAY_DEFAULT "background-color: #444A49; color: #F4EAEA; border-radius: 10px;"
#define STYLE_DISPLAY_ERROR "background-color: #444A49; color: #F99494; border-radius: 10px;"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    ui->setupUi(this);

    QString button_style = "QPushButton { border: none; background-color: #C4C4C4; } QPushButton:pressed { background-color: #B5B5B5; }";
    QString button_style_darker = "QPushButton { border: none; background-color: #A59E9E; } QPushButton:pressed { background-color: #9C9292; }";

    ui->pushButton_equal->setStyleSheet(button_style_darker);
    ui->pushButton_clear->setStyleSheet(button_style_darker);
    ui->pushButton_comma->setStyleSheet(button_style);
    ui->pushButton_divide->setStyleSheet(button_style);
    ui->pushButton_power->setStyleSheet(button_style);
    ui->pushButton_square->setStyleSheet(button_style);
    ui->pushButton_l_bracket->setStyleSheet(button_style);
    ui->pushButton_r_bracket->setStyleSheet(button_style);

    // Manually connect digit buttons.

    vector<QPushButton*> digit_buttons = {
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
    };

    for (QPushButton* button : digit_buttons) {
        button->setStyleSheet(button_style);
        connect(button, SIGNAL(released()), this, SLOT(press_digit()));
    }

    // And operators that simply append.

    vector<QPushButton*> simple_operator_buttons = {
        ui->pushButton_plus,
        ui->pushButton_minus,
        ui->pushButton_multiply,
        ui->pushButton_divide,
    };

    for (QPushButton* button : simple_operator_buttons) {
        button->setStyleSheet(button_style);
        connect(button, SIGNAL(released()), this, SLOT(press_simple_operator()));
    }

    this->on_pushButton_clear_released();

    // Add a shortcut for copy
    new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_C), this, SLOT(copy_result()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set_display(QString expr) {
    if (this->lastToken == NONE) {
        ui->label->setStyleSheet(STYLE_DISPLAY_DEFAULT);
    }

    ui->label->setText(expr);
}

void MainWindow::display_error(int error_code) {
    qDebug() << "Error code:" << error_code;

    QString error_message;

    if (error_code >= ERROR_MESSAGES) {
        qDebug() << "No messagee for error code" << error_code;
        error_message = "err code " + QString::number(error_code, 10);
    } else {
        error_message = error_messages[error_code];
    }

    ui->label->setStyleSheet(STYLE_DISPLAY_ERROR);
    this->set_display("ERR: " + error_message);

    this->lastToken = NONE;
    this->empty = true;
    this->stop_number();
}

void MainWindow::append_to_expression(QString expr, bool force_append) {
    QString final_expression;
    if (this->empty && !force_append) {
        final_expression = expr;

        this->empty = false;
    } else {
        final_expression = ui->label->text() + expr;

        if (force_append) {
            this->empty = false;
        }
    }

    this->set_display(final_expression);
}

void MainWindow::append_to_expression(QString expr) {
    this->append_to_expression(expr, false);
}

void MainWindow::reset() {
    this->empty = true;
    this->lastToken = DIGIT;
    this->paren_count = 0;
}

void MainWindow::stop_number() {
    this->building_number = false;
    this->has_comma = false;
}

// Slots

void MainWindow::append_digit(QString digit)
{
    this->append_to_expression(digit);
    this->lastToken = DIGIT;
    this->building_number = true;
}

// Simply append any digits to the expression.
void MainWindow::press_digit()
{
    QPushButton * button = (QPushButton*)sender();
    this->append_digit(button->text());
}

// Simply append any operators that don't require any extra work or checks.
void MainWindow::press_simple_operator() {
    QPushButton * button = (QPushButton*)sender();

    if (this->lastToken == OPERATOR || this->lastToken == NONE) {
        qDebug() << "Last token was operator, not appending.";
        return;
    }

    if (this->empty) {
        qDebug() << "Cannot start with an operator, not appending.";
        return;
    }

    this->append_to_expression(button->text());
    this->lastToken = OPERATOR;
    this->stop_number();
}

// Clear
void MainWindow::on_pushButton_clear_released()
{
    this->set_display("0");
    this->has_comma = false;
    this->building_number = true;
    this->reset();
}

// Evaluate
void MainWindow::on_pushButton_equal_released()
{
    // Evaluate expression in the display label.

    QString qExpression = ui->label->text();

    double result;

    try {
        result = this->calc.processInput(qExpression.trimmed().toUtf8().constData());
    } catch (ErrorCode error_code) {
        this->display_error(error_code);
        return;
    }

    QString qResult = QString::number(result, 'g', 12);

    ui->label->setText(qResult);

    if (qResult.contains(".")) {
        this->has_comma = true;
    } else {
        this->has_comma = false;
    }

    this->lastToken = DIGIT;
    this->building_number = true;
}

// Open parenthesses
void MainWindow::on_pushButton_l_bracket_released()
{
    QPushButton * button = (QPushButton*)sender();

    // Can open parenthesses only after operators.
    if (this->lastToken != OPERATOR && this->empty == false) {
        qDebug() << "Open parenthesses not after an operator, not appending.";
        return;
    }

    this->append_to_expression(button->text());
    this->lastToken = OPEN_PAREN;
    this->paren_count++;
    this->stop_number();
}


// Close parenthesses
void MainWindow::on_pushButton_r_bracket_released()
{
    QPushButton * button = (QPushButton*)sender();

    if (this->paren_count == 0) {
        qDebug() << "No open parenthesses to close, not appending.";
        return;
    }

    // Cannot have an empty parenthesses
    if (this->lastToken == OPEN_PAREN) {
        qDebug() << "Empty parenthesses, not appending.";
        return;
    }

    // Closing parentheesses with an operator inside.
    if (this->lastToken == OPERATOR) {
        qDebug() << "Cannot close after operator.";
        return;
    }

    this->append_to_expression(button->text());
    this->lastToken = CLOSE_PAREN;
    this->paren_count--;
    this->stop_number();
}


// Square
void MainWindow::on_pushButton_square_released()
{
    QPushButton * button = (QPushButton*)sender();

    if (this->lastToken == DIGIT && !this->empty) {
        qDebug() << "Square after digit, not appending.";
        return;
    }

    this->append_to_expression(button->text());
    this->lastToken = OPERATOR;
    this->stop_number();
}


// Power
void MainWindow::on_pushButton_power_released()
{
    // There has to be a number on the left.
    if (this->lastToken != DIGIT && this->lastToken != CLOSE_PAREN && this->lastToken != FACT) {
        qDebug() << "Left side of power invalid, not appending.";
        return;
    }

    if (this->empty) {
        qDebug() << "Cannot start with power, not appending.";
        return;
    }

    this->append_to_expression("^");
    this->lastToken = OPERATOR;
    this->stop_number();
}


// Factorial
void MainWindow::on_pushButton_fact_released()
{
    // There has to be a number on the left side.
    if (this->lastToken != DIGIT && this->lastToken != CLOSE_PAREN) {
        qDebug() << "Left side of fact invalid, not appending.";
        return;
    }

    if (this->empty) {
        qDebug() << "Cannot start with an operator, not appending.";
        return;
    }

    this->append_to_expression("!");
    this->lastToken = FACT;
    this->stop_number();
}


void MainWindow::on_pushButton_comma_released()
{
    if (!this->building_number) {
        qDebug() << "Cannot insert comma outside a number, not appending.";
        return;
    }

    if (this->has_comma) {
        qDebug() << "Decimal numbers cannot have multiple commas, not appending.";
        return;
    }

    this->append_to_expression(".", true);
    this->lastToken = COMMA;
    this->has_comma = true;
}

void MainWindow::copy_result()
{
    QClipboard *clipboard = QGuiApplication::clipboard();
    QString content = ui->label->text();

    clipboard->setText(content);
}

void MainWindow::on_pushButton_hint_released()
{
    QMessageBox msgBox;
    QString msg = tr(
        "                          Napoveda                           \n \
        Cislice 0-9 zadavaju cisla do panela\n \
        Funkcia '+' scitava cisla\n \
        Funkcia '-' odcitava cisla\n \
        Funkcia '*' nasobi cisla\n \
        Funkcia '/' deli cisla\n \
        Funkcia '!' urobi faktorial cisla\n \
        Funkcia '√' odmocni cislo\n \
        Funkcia '^' urobi mocninu cisla\n \
        Funkcia 'C' vymaze panel\n \
        Funkcia '=' vyhodnoti vyraz"
    );
    msgBox.setText(msg);
    msgBox.exec();
}

