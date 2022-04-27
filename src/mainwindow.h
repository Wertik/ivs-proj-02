#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mathlib/mathlib.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum Token {
   NONE,
   DIGIT,
   OPERATOR,
   FACT,
   OPEN_PAREN,
   CLOSE_PAREN,
   COMMA
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Calculator calc;

    bool empty = true;
    Token lastToken = NONE;

    bool building_number = false;
    bool has_comma = false;

    // Count the number of open parenthesses.
    int paren_count = 0;

    void set_expression(QString expr);
    void append_to_expression(QString expr, bool force_append);
    void append_to_expression(QString expr);
    void append_digit(QString digit);
    void reset();

    void stop_number();

private slots:        
    void press_digit();
    void press_simple_operator();

    void on_pushButton_clear_released();
    void on_pushButton_equal_released();

    void on_pushButton_l_bracket_released();
    void on_pushButton_r_bracket_released();

    void on_pushButton_square_released();
    void on_pushButton_power_released();
    void on_pushButton_fact_released();
    void on_pushButton_comma_released();

    void copy_result();
};
#endif // MAINWINDOW_H
