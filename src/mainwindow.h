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
   COMMA,
};

// Avoid segfault in case someone forgot to add a message after adding a new error code.
#define ERROR_MESSAGES 9

const QString error_messages[ERROR_MESSAGES] {
    "Dělení nulou",
    "Záporný faktoriál",
    "Faktoriál přetekl",
    "Faktoriál není celé číslo",
    "Odmocnitel není celé číslo",
    "Odmocnitel menší než 1",
    "Záporná odmocnina",
    "Nelze zpracovat výraz",
    "Chybné zadání"
};

// The lowest font size
#define FONT_MIN 18
// Font size decrease per width step
#define FONT_STEP 2
// When to start shrinking the font
#define CHARACTER_THRESHOLD 15
// Default font size
#define FONT_DEFAULT 36
// Maximum number of characters
#define CHARACTER_LIMIT 30

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

    QString fill_font_size(QString style);

    void set_display(QString expr, bool error);
    void set_display(QString expr);

    void display_error(int error_code);

    void append_to_expression(QString expr, bool force_append);
    void append_to_expression(QString expr);
    void append_digit(QString digit);
    void reset();

    void stop_number();

private slots:        
    void press_digit();

    void press_sign();
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
    void on_pushButton_hint_released();
};
#endif // MAINWINDOW_H
