#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QShortcut>
#include <QClipboard>
#include <QMessageBox>

using namespace std;

#define STYLE_DISPLAY_DEFAULT "background-color: #444A49; color: #F4EAEA; border-radius: 10px; font-size: %%FONT_SIZEpx;"
#define STYLE_DISPLAY_ERROR "background-color: #444A49; color: #F99494; border-radius: 10px; font-size: %%FONT_SIZEpx;"

/**
 * @brief MainWindow function
 * @param parent
 */
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

    // Operators that only append.

    vector<QPushButton*> simple_operator_buttons = {
        ui->pushButton_multiply,
        ui->pushButton_divide,
    };

    for (QPushButton* button : simple_operator_buttons) {
        button->setStyleSheet(button_style);
        connect(button, SIGNAL(released()), this, SLOT(press_simple_operator()));
    }

    // Signs (plus and minus)

    vector<QPushButton*> sign_operators = {
        ui->pushButton_plus,
        ui->pushButton_minus,
    };

    for (QPushButton* button : sign_operators) {
        button->setStyleSheet(button_style);
        connect(button, SIGNAL(released()), this, SLOT(press_sign()));
    }

    this->on_pushButton_clear_released();

    // Add a shortcut for copy
    new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_C), this, SLOT(copy_result()));
    qDebug() << fill_font_size(STYLE_DISPLAY_DEFAULT);
    ui->label->setStyleSheet(fill_font_size(STYLE_DISPLAY_DEFAULT));
}

/**
 * @brief Function to delete ui
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @param QString style to work with.
 *
 * @brief Figures out the ideal font size for the label given it's text length.
 * Takes a given @param style, replaces the placeholder %%FONT_SIZE with font size and returns it.
 *
 * @return QString Style with replaced %%FONT_SIZE placeholder.
 */
QString MainWindow::fill_font_size(QString style) {
    int width = (int) ui->label->text().size();

    qDebug() << "Width" << width;

    int font_size = FONT_DEFAULT;

    // Under threshold
    if (width >= CHARACTER_THRESHOLD) {
        font_size = max(FONT_MIN, FONT_DEFAULT - (width - CHARACTER_THRESHOLD) * FONT_STEP);
    }

    qDebug() << "Font size:" << font_size;

    style = style.replace("%%FONT_SIZE", QString::number(font_size, 10, 0));
    return style;
}

/**
 * @brief Function to set display
 * @param expr expression to be set
 */
void MainWindow::set_display(QString expr, bool error) {
    ui->label->setText(expr);

    if (error) {
        ui->label->setStyleSheet(fill_font_size(STYLE_DISPLAY_ERROR));
    } else {
        ui->label->setStyleSheet(fill_font_size(STYLE_DISPLAY_DEFAULT));
    }
}

void MainWindow::set_display(QString expr) {
    this->set_display(expr, false);
}

/**
 * @brief Function for displaying errors
 * @param error_code number of error
 */
void MainWindow::display_error(int error_code) {
    qDebug() << "Error code:" << error_code;

    QString error_message;

    if (error_code >= ERROR_MESSAGES) {
        qDebug() << "No messagee for error code" << error_code;
        error_message = "err code " + QString::number(error_code, 10);
    } else {
        error_message = error_messages[error_code];
    }

    this->set_display("ERR: " + error_message, true);

    this->lastToken = NONE;
    this->empty = true;
    this->stop_number();
}

/**
 * @brief Function for appending expression
 * @param expr expression to append
 * @param force_append 
 */
void MainWindow::append_to_expression(QString expr, bool force_append) {
    QString final_expression;
    if (this->empty && !force_append) {
        final_expression = expr;

        this->empty = false;
    } else {
        final_expression = ui->label->text() + expr;

        if (final_expression.size() > CHARACTER_LIMIT) {
            return;
        }

        if (force_append) {
            this->empty = false;
        }
    }

    this->set_display(final_expression);
}

/**
 * @brief Function for appending expression
 * @param expr expression that is being appended
 */
void MainWindow::append_to_expression(QString expr) {
    this->append_to_expression(expr, false);
}

/**
 * @brief Reset function
 */
void MainWindow::reset() {
    this->empty = true;
    this->lastToken = DIGIT;
    this->paren_count = 0;
}

/**
 * @brief Stop_number function
 */
void MainWindow::stop_number() {
    this->building_number = false;
    this->has_comma = false;
}

// Slots
/**
 * @brief Function appends digits to the expression
 */
void MainWindow::append_digit(QString digit)
{
    this->append_to_expression(digit);
    this->lastToken = DIGIT;
    this->building_number = true;
}

// Simply append any digits to the expression.
/**
 * @brief Function appends digits to the expression after receives press signal
 */
void MainWindow::press_digit()
{
    QPushButton * button = (QPushButton*)sender();
    this->append_digit(button->text());
}

// Plus and minus
/**
 * @brief Function deal with plus and minus sign
 */
void MainWindow::press_sign() {
    QPushButton * button = (QPushButton*)sender();

    if (this->lastToken == OPERATOR || this->lastToken == NONE) {
        qDebug() << "Last token was operator, not appending.";
        return;
    }

    this->append_to_expression(button->text());
    this->lastToken = OPERATOR;
    this->stop_number();
}

// Simply append any operators that don't require any extra work or checks.
/**
 * @brief Function appends operators
 */
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
/**
 * @brief Function clears the calculator panel
 */
void MainWindow::on_pushButton_clear_released()
{
    this->set_display("0");
    ui->label->setStyleSheet(fill_font_size(STYLE_DISPLAY_DEFAULT));

    this->has_comma = false;
    this->building_number = true;
    this->reset();
}

// Evaluate
/**
 * @brief Function evaluate expression and gives the result to the calculator panel
 */
void MainWindow::on_pushButton_equal_released()
{
    // Evaluate expression in the display label.

    QString qExpression = ui->label->text();

    // Replace √ with _ (used by the parser for sqrt)
    // Replace , with . (used in stod instead of a comma)
    qExpression = qExpression
            .replace("√", "_")
            .replace(",", ".");

    double result;

    try {
        result = this->calc.processInput(qExpression.trimmed().toUtf8().constData());
    } catch (ErrorCode error_code) {
        this->display_error(error_code);
        return;
    }

    QString qResult = QString::number(result, 'g', 12);

    // Replace . back to ,
    qResult = qResult.replace(".", ",");

    ui->label->setText(qResult);
    ui->label->setStyleSheet(fill_font_size(STYLE_DISPLAY_DEFAULT));

    if (qResult.contains(".")) {
        this->has_comma = true;
    } else {
        this->has_comma = false;
    }

    this->lastToken = DIGIT;
    this->building_number = true;
}

// Open parenthesses
/**
 * @brief Function checks left brackets
 */
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
/**
 * @brief Function checks right brackets
 */
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
/**
 * @brief Function resolve square after received release signal
 */
void MainWindow::on_pushButton_square_released()
{
    QPushButton * button = (QPushButton*)sender();

    // There has to be a number on the left.
    if (this->lastToken != DIGIT && this->lastToken != CLOSE_PAREN && this->lastToken != FACT) {
        qDebug() << "Left side of square invalid, not appending.";
        return;
    }

    if (this->empty) {
        qDebug() << "Cannot start with square, not appending.";
        return;
    }

    this->append_to_expression(button->text());
    this->lastToken = OPERATOR;
    this->stop_number();
}


// Power
/**
 * @brief Function resolve power after received release signal
 */
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
/**
 * @brief Function resolve factorial after received release signal
 */
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

/**
 * @brief Function releases comma to the calculator panel
 */
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

    this->append_to_expression(",", true);
    this->lastToken = COMMA;
    this->has_comma = true;
}

/**
 * @brief Function copy result from the calculator panel
 */
void MainWindow::copy_result()
{
    QClipboard *clipboard = QGuiApplication::clipboard();
    QString content = ui->label->text();

    clipboard->setText(content);
}

/**
 * @brief Popup window with hint how to use calculator
 */
void MainWindow::on_pushButton_hint_released()
{
    QMessageBox msgBox;
    QString msg = tr(
        "<h1>Nápověda</h1> \
         <h2>Tlačítka</h2> \
        Číslice 0-9 zadávají čisla do displaye<br /> \
        Funkce '+' sčítá čísla (použití -> x+y)<br /> \
        Funkce '-' odčitáva čísla (použití -> x-y)<br /> \
        Funkce '*' nasobí čísla (použití -> x*y)<br /> \
        Funkce '/' dělí čísla (použití -> x/y)<br /> \
        Funkce '!' urobí faktoriál čísla (použití -> !x)<br /> \
        Funkce '√' odmocní čislo (použití -> y√x)<br /> \
        Funkce '^' urobí mocninu čísla (použití -> x^y)<br /> \
        Funkce 'C' vymaže display<br /> \
        Funkce '=' vyhodnoti vyraz \
        \
        <h2>Klávesové zkratky</h2> \
        <style>table { border-collapse: collapse; } td { text-align: left; } tr { border-bottom: 1pt solid white; }</style>  \
        <table>\
            <tr><th>Zkratka</th><th>Akce</th></tr> \
            <tr><td>Num 0</td> <td>0</td></tr> \
            <tr><td>Num 1</td> <td>1</td></tr> \
            <tr><td>Num 2</td> <td>2</td></tr> \
            <tr><td>Num 3</td> <td>3</td></tr> \
            <tr><td>Num 4</td> <td>4</td></tr> \
            <tr><td>Num 5</td> <td>5</td></tr> \
            <tr><td>Num 6</td> <td>6</td></tr> \
            <tr><td>Num 7</td> <td>7</td></tr> \
            <tr><td>Num 8</td> <td>8</td></tr> \
            <tr><td>Num 9</td> <td>9</td></tr> \
            <tr><td>/</td> <td>/</td></tr> \
            <tr><td>*</td> <td>*</td></tr> \
            <tr><td>-</td> <td>-</td></tr> \
            <tr><td>+</td> <td>+</td></tr> \
            <tr><td>Enter</td> <td>=</td></tr> \
            <tr><td>, (delimiter)</td> <td>,</td></tr> \
            <tr><td>Šipka vlevo</td> <td>(</td></tr> \
            <tr><td>Šipka vpravo</td> <td>)</td></tr> \
            <tr><td>Šipka nahoru</td> <td>Mocnina</td></tr> \
            <tr><td>Šipka dolu</td> <td>Odmocnina</td></tr> \
            <tr><td>Ctrl + C</td> <td>Zkopírování hodnoty z displaye</td></tr> \
            <tr><td>Delete</td> <td>Vymazání displaye</td></tr> \
            <tr><td><span style=\"color: #6C7673;\">-------------------</span></td><td><span style=\"color: #6C7673;\">--------------------</span></td></tr>\
        </table> \
        \
        <br /><br />\
        Aplikace vytvořena v rámci projektu předmětu IVS, VUT FIT.<br />\
        CMYK Team, 28. 4. 2022 \
    ");
    msgBox.setText(msg);
    msgBox.setWindowTitle("Kalkulačka - Nápověda");
    msgBox.setStyleSheet("color: #F4EAEA; background-color: #6C7673; font-size: 14px;");
    msgBox.exec();
}
