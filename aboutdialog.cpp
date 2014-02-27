#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    connect(ui->buttons, SIGNAL(rejected()), this, SLOT(close()));

    setWindowTitle("About QArduControl");
    ui->appname->setText("QArduControl");
    ui->appdetails->setText("Burn once and control your Arduino board via USB/Serial");
    ui->appversion->setText("1.0");
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
