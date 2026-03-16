#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QObject>
#include <QQueue>
#include <QString>

class Calculator : public QObject
{
    Q_OBJECT

    // Display value - what user sees on screen
    Q_PROPERTY(QString displayValue READ displayValue NOTIFY displayValueChanged)

    // Final result after calculation
    Q_PROPERTY(double result READ result NOTIFY resultChanged)

public:
    explicit Calculator(QObject *parent = nullptr);

    // Getter functions
    QString displayValue() const;
    double result() const;

public slots:
    // ============== CALLABLE FROM QML ==============

    // Called when digit buttons (0-9) are pressed
    void digitPressed(int digit);

    // Called when decimal point (.) is pressed
    void decimalPressed();

    // Called when operation buttons (+, -, ×, ÷) are pressed
    void operationPressed(const QString &operation);

    // Called when equals (=) button is pressed
    void equalPressed();

    // Called when clear (C) button is pressed
    void clear();

    // Called when backspace is pressed (optional)
    void backspace();

signals:
    void displayValueChanged();
    void resultChanged();
    void errorOccurred(const QString &errorMessage);

private:
    // ============== HELPER FUNCTIONS ==============
    void pushCurrentNumber();
    double performCalculation();
    double applyOperation(double num1, double num2, const QString &op);
    void updateDisplay(const QString &value);

    // ============== MEMBER VARIABLES ==============
    QQueue<double> m_numbersQueue;      // Queue to store numbers
    QQueue<QString> m_operationsQueue;  // Queue to store operations
    QString m_currentInput;              // Current number being typed
    QString m_displayValue;              // What's shown on display
    double m_result;                     // Final calculation result
    bool m_newCalculation;               // Flag for new calculation after =
};

#endif // CALCULATOR_H
