#include "calculator.h"
#include <QDebug>

Calculator::Calculator(QObject *parent)
    : QObject(parent)
    , m_currentInput("")
    , m_displayValue("0")
    , m_result(0.0)
    , m_newCalculation(false)
{
}

// ============== GETTER FUNCTIONS ==============

QString Calculator::displayValue() const
{
    return m_displayValue;
}

double Calculator::result() const
{
    return m_result;
}

// ============== SLOT: DIGIT PRESSED ==============

void Calculator::digitPressed(int digit)
{

    // If starting new calculation after pressing =
    if (m_newCalculation) {
        clear();
        m_newCalculation = false;
    }

    // Prevent leading zeros (except for "0.")
    if (m_currentInput == "0" && digit == 0) {
        return;
    }

    // Replace initial "0" with the digit
    if (m_currentInput == "0" || m_currentInput.isEmpty()) {
        m_currentInput = QString::number(digit);
    } else {
        // Append digit to current input
        m_currentInput.append(QString::number(digit));
    }

    updateDisplay(m_currentInput);
}

// ============== SLOT: DECIMAL PRESSED ==============

void Calculator::decimalPressed()
{

    if (m_newCalculation) {
        clear();
        m_newCalculation = false;
    }

    // Prevent multiple decimal points
    if (m_currentInput.contains('.')) {
        return;
    }

    // If empty, start with "0."
    if (m_currentInput.isEmpty()) {
        m_currentInput = "0.";
    } else {
        m_currentInput.append('.');
    }

    updateDisplay(m_currentInput);
}

// ============== SLOT: OPERATION PRESSED ==============

void Calculator::operationPressed(const QString &operation)
{

    // If we just calculated, use the result as first number
    if (m_newCalculation) {
        m_newCalculation = false;
        m_currentInput = QString::number(m_result);
        m_numbersQueue.clear();
        m_operationsQueue.clear();
    }

    // Push current number to queue
    pushCurrentNumber();

    // Push operation to queue
    m_operationsQueue.enqueue(operation);

    // Clear current input for next number
    m_currentInput = "";
}

// ============== SLOT: EQUAL PRESSED ==============

void Calculator::equalPressed()
{
    // Push the last number
    pushCurrentNumber();

    // Need at least 2 numbers and 1 operation
    if (m_numbersQueue.size() < 2 || m_operationsQueue.isEmpty()) {

        // If only one number, just show it
        if (m_numbersQueue.size() == 1) {
            m_result = m_numbersQueue.dequeue();
            updateDisplay(QString::number(m_result));
        }
        return;
    }

    // Perform calculation
    m_result = performCalculation();

    // Update display with result
    // Remove trailing zeros for cleaner display
    QString resultStr = QString::number(m_result, 'g', 10);
    updateDisplay(resultStr);

    emit resultChanged();

    // Set flag for new calculation
    m_newCalculation = true;
}

// ============== SLOT: CLEAR ==============

void Calculator::clear()
{

    m_numbersQueue.clear();
    m_operationsQueue.clear();
    m_currentInput = "";
    m_displayValue = "0";
    m_result = 0.0;
    m_newCalculation = false;

    emit displayValueChanged();
    emit resultChanged();
}

// ============== SLOT: BACKSPACE ==============

void Calculator::backspace()
{
    if (m_newCalculation) {
        clear();
        return;
    }

    if (!m_currentInput.isEmpty()) {
        m_currentInput.chop(1);  // Remove last character

        if (m_currentInput.isEmpty()) {
            updateDisplay("0");
        } else {
            updateDisplay(m_currentInput);
        }
    }
}

// ============== PRIVATE: PUSH CURRENT NUMBER ==============

void Calculator::pushCurrentNumber()
{
    if (m_currentInput.isEmpty()) {
        // If no input, don't push anything
        // Or push 0 if needed
        return;
    }

    bool ok;
    double number = m_currentInput.toDouble(&ok);

    if (ok) {
        m_numbersQueue.enqueue(number);
    } else {
        emit errorOccurred("Invalid number input");
    }
}

// ============== PRIVATE: PERFORM CALCULATION ==============

double Calculator::performCalculation()
{
    if (m_numbersQueue.isEmpty()) {
        return 0.0;
    }

    // Get first number
    double result = m_numbersQueue.dequeue();

    // Process each operation with next number
    while (!m_operationsQueue.isEmpty() && !m_numbersQueue.isEmpty()) {
        QString op = m_operationsQueue.dequeue();
        double nextNumber = m_numbersQueue.dequeue();

        result = applyOperation(result, nextNumber, op);
    }

    // Clear queues after calculation
    m_numbersQueue.clear();
    m_operationsQueue.clear();

    return result;
}

// ============== PRIVATE: APPLY OPERATION ==============

double Calculator::applyOperation(double num1, double num2, const QString &op)
{
    if (op == "+") {
        return num1 + num2;
    }
    else if (op == "-") {
        return num1 - num2;
    }
    else if (op == "×" || op == "*") {
        return num1 * num2;
    }
    else if (op == "÷" || op == "/") {
        if (num2 == 0.0) {
            emit errorOccurred("Error: Division by zero!");
            return 0.0;
        }
        return num1 / num2;
    }
    return num1;
}

// ============== PRIVATE: UPDATE DISPLAY ==============

void Calculator::updateDisplay(const QString &value)
{
    if (m_displayValue != value) {
        m_displayValue = value;
        emit displayValueChanged();
    }
}
