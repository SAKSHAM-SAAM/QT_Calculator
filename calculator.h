#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;
private slots:
    void NumPressed();
    void MathButtonPressed();
    void EqualButton();
    void ChangeNumberSign();
    void AllClear();
    void MemoryPressed();

    void Square();
    void Root();
    void Exponent();
    void ten();

    void Percent();
    void Factorial();
    void ScreenClear();
    void Backspace();
};
#endif // CALCULATOR_H
