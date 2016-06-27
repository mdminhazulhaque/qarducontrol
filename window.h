#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTimer>
#include <QTime>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include "aboutdialog.h"

namespace Ui {
class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();

private slots:
    void digitalWrite(int value);
    void analogWrite(int value);
    void analogRead();
    void quit();
    void connectToArduino();
    void softwareReset();

private:
    Ui::Window *ui;
    AboutDialog *about;
    QSerialPort *arduino;
    QTimer analogReader;
};

#endif // WINDOW_H
