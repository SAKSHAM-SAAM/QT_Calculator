#include "calculator.h"
#include "ui_calculator.h"
#include <QRegularExpression>
#include <QtMath>

double CalcVal   = 0.0;
bool divTrigger  = false;
bool multTrigger = false;
bool subTrigger  = false;
bool addTrigger  = false;
double MemoryVar = 0.0;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(CalcVal));

    // binding numerical event
    QPushButton* numButtons[10];
    for(int i=0;i<10; i++)
    {
        QString buttonName = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(buttonName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }
    // binding Arithmentic Events
    connect(ui->Add, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    // binding equal Event
    connect(ui->Equal, SIGNAL(released()), this, SLOT(EqualButton()));
    // binding change sign Event
    connect(ui->ChangeSign, SIGNAL(released()), this, SLOT(ChangeNumberSign()));
    // binding all clear Event
    connect(ui->Clear, SIGNAL(released()), this, SLOT(AllClear()));
    // binding all memory Event
    connect(ui->MemSet, SIGNAL(released()), this, SLOT(MemoryPressed()));
    connect(ui->MemGet, SIGNAL(released()), this, SLOT(MemoryPressed()));
    connect(ui->MemClear, SIGNAL(released()), this, SLOT(MemoryPressed()));
    // binding Special Events
    connect(ui->Sqr, SIGNAL(released()), this, SLOT(Square()));
    connect(ui->Sqrt, SIGNAL(released()), this, SLOT(Root()));
    connect(ui->Exp, SIGNAL(released()), this, SLOT(Exponent()));
    connect(ui->tenfold, SIGNAL(released()), this, SLOT(ten()));

    connect(ui->Percent, SIGNAL(released()), this, SLOT(Percent()));
    connect(ui->ClearScreen, SIGNAL(released()), this, SLOT(ScreenClear()));
    connect(ui->BackSpace, SIGNAL(released()), this, SLOT(Backspace()));
    connect(ui->Factorial, SIGNAL(released()), this, SLOT(Factorial()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed()
{
    QPushButton *button = (QPushButton *)sender();

        // Get number on button
        QString buttonVal = button->text();
        QString displayVal = ui->Display->text();

        if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)){
            ui->Display->setText(buttonVal);
        } else {
            QString newVal = displayVal + buttonVal;
            double dblNewVal = newVal.toDouble();
            ui->Display->setText(QString::number(dblNewVal, 'g', 16));
        }
}

void Calculator::MathButtonPressed()
{
    // Reset all previous maths events
    divTrigger = false;
    multTrigger = false;
    subTrigger = false;
    addTrigger = false;

    // Retrieve previous value and save it in CalcVal global
    QString DisplayValue = ui->Display->text();
    CalcVal              = DisplayValue.toDouble();
    QPushButton* button  = (QPushButton* )sender();
    QString buttonValue  = button->text();

    // Find the Event triggered
    if(QString::compare(buttonValue,"/",Qt::CaseInsensitive) == 0)
    {
        divTrigger = true;
    }else if(QString::compare(buttonValue,"*",Qt::CaseInsensitive) == 0)
    {
        multTrigger = true;
    }else if(QString::compare(buttonValue,"-",Qt::CaseInsensitive) == 0)
    {
        subTrigger = true;
    }else
    {
        addTrigger = true;
    }

    // Update Display Value
    ui->Display->setText(QString::number(0.0));
}

void Calculator::EqualButton()
{
    double solution      = 0.0;
    double dblDisplayVal = ui->Display->text().toDouble();

    if(divTrigger || multTrigger || subTrigger || addTrigger)
    {
        if(addTrigger)
        {
            solution = CalcVal + dblDisplayVal;
        }else if(subTrigger)
        {
            solution = CalcVal - dblDisplayVal;
        }else if(multTrigger)
        {
            solution = CalcVal * dblDisplayVal;
        }else if(divTrigger)
        {
            solution = CalcVal/dblDisplayVal;
        }
    }
    ui->Display->setText(QString::number(solution, 'g', 8));
    CalcVal=solution;
}

void Calculator::ChangeNumberSign()
{
    QString DisplayVal = ui->Display->text();
    QRegularExpression reg("[-]?[0-9]*");
    QRegularExpressionMatch match = reg.match(DisplayVal);
    if(match.hasMatch())
    {
        double dblValue = DisplayVal.toDouble();
        dblValue = -1 * dblValue;
        ui->Display->setText(QString::number(dblValue));
    }
}

void Calculator::AllClear(){
    CalcVal = 0.0;
    ui->Display->setText(QString::number(0.0));
}

void Calculator::MemoryPressed()
{
    QPushButton* button = (QPushButton* )sender();
    QString Operation   = button->text();

    if(QString::compare(Operation,"M+",Qt::CaseInsensitive) == 0)
    {
        MemoryVar = ui->Display->text().toDouble();
    }else if(QString::compare(Operation,"M-",Qt::CaseInsensitive) == 0)
    {
        MemoryVar = 0.0;
    }else{
        ui->Display->setText(QString::number(MemoryVar));
    }

}

void Calculator::Square()
{
    double dblDisplayVal = ui->Display->text().toDouble();
    double answer = dblDisplayVal * dblDisplayVal;
    ui->Display->setText(QString::number(answer));
}
void Calculator::Root()
{
    double dblDisplayVal = ui->Display->text().toDouble();
    double answer = sqrt(dblDisplayVal);
    ui->Display->setText(QString::number(answer));
}
void Calculator::Exponent()
{
    ui->Display->setText(QString::number(2.71828));
}
void Calculator::ten()
{
    double dblDisplayVal = ui->Display->text().toDouble();
    double answer = dblDisplayVal * 10;
    ui->Display->setText(QString::number(answer));
}

void Calculator::Percent()
{
    double dblDisplayVal = ui->Display->text().toDouble();
    double answer = dblDisplayVal / 100;
    ui->Display->setText(QString::number(answer));
}
void Calculator::Factorial()
{
    double dblDisplayVal = ui->Display->text().toInt();
    double fact = 1;
    for(int i=dblDisplayVal;i>=2;i--)
    {
        fact=fact*i;
    }
    ui->Display->setText(QString::number(fact));
}
void Calculator::ScreenClear()
{
    ui->Display->setText("0");
}
void Calculator::Backspace()
{
    double dblDisplayVal = ui->Display->text().toDouble();
    int answer = dblDisplayVal / 10;
    ui->Display->setText(QString::number(answer));
}
