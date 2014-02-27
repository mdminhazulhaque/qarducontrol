#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::Window)
{
    ui->setupUi(this);
    setWindowTitle("QArduControl");
    arduino = new QSerialPort(this);
    about = new AboutDialog(this);

    for(int i=0; i<ui->grid_digital_write->count(); i++)
        connect(ui->grid_digital_write->itemAt(i)->widget(), SIGNAL(stateChanged(int)),
                this, SLOT(digitalWrite(int)));

    for(int i=0; i<ui->grid_analog_write->count(); i++)
        if(ui->grid_analog_write->itemAt(i)->widget()->objectName().startsWith("pwm_"))
            connect(ui->grid_analog_write->itemAt(i)->widget(), SIGNAL(valueChanged(int)),
                    this, SLOT(analogWrite(int)));

    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(quit()));
    connect(ui->actionReset, SIGNAL(triggered()), this, SLOT(softwareReset()));
    connect(ui->actionAbout, SIGNAL(triggered()), about, SLOT(show()));
    connect(ui->button_connect, SIGNAL(clicked()), this, SLOT(connectToArduino()));

    ui->frame_controls->setDisabled(true);
    ui->statusBar->showMessage("Ready to connect");
}

Window::~Window()
{
    delete ui;
}

void Window::digitalWrite(int value)
{
    int pin = sender()->objectName().remove("check_digital_").toInt();
    arduino->write(QString("d %1 %2)").arg(pin).arg(value).toAscii());
    //qDebug() << "digitalWrite(" << pin << "," << value << ");";
}

void Window::analogWrite(int value)
{
    int pin = sender()->objectName().remove("pwm_").toInt();
    //qDebug() << "analogWrite(" << pin << "," << value << ");";
    arduino->write(QString("a %1 %2)").arg(pin).arg(value).toAscii());
}

void Window::analogRead()
{
    QList<QByteArray> serial = arduino->readLine().trimmed().split(' ');
    ui->statusBar->showMessage(QString("Uptime %1 miliseconds").arg(serial.value(0).toInt()));
    ui->analog_0->setValue(serial.value(1).toInt());
    ui->analog_1->setValue(serial.value(2).toInt());
    ui->analog_2->setValue(serial.value(3).toInt());
    ui->analog_3->setValue(serial.value(4).toInt());
    ui->analog_4->setValue(serial.value(5).toInt());
    ui->analog_5->setValue(serial.value(6).toInt());
}

void Window::quit()
{
    if(arduino->isOpen())
        arduino->close();
    qApp->quit();
}

void Window::connectToArduino()
{
    bool connected = arduino->isOpen();

    if(connected)
    {
        arduino->close();
        analogReader.stop();
        ui->statusBar->showMessage("Disconnected");
        ui->frame_controls->setDisabled(true);
        ui->button_connect->setText("Connect");
    }
    else
    {
        arduino->setPortName(ui->combo_device->currentText());
        if(arduino->open(QSerialPort::ReadWrite))
        {
            arduino->setBaudRate(QSerialPort::Baud9600);
            arduino->setDataBits(QSerialPort::Data8);
            arduino->setParity(QSerialPort::NoParity);
            arduino->setStopBits(QSerialPort::OneStop);
            arduino->setFlowControl(QSerialPort::NoFlowControl);

            ui->frame_controls->setEnabled(true);
            ui->button_connect->setText("Disconnect");

            connect(&analogReader, SIGNAL(timeout()), this, SLOT(analogRead()));
            analogReader.start(500);
            analogRead();
        }
    }
}

void Window::softwareReset()
{
    arduino->write("r");
}
