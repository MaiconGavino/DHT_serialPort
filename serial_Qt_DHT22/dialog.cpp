#include "dialog.h"
#include "ui_dialog.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <string>
#include <QDebug>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    arduino = new QSerialPort(this);
    ui->Lcd->display("-----");


    /* Identificar a porta, o ID do fornecedor e o ID do produto
        qDebug() << "Porta Numero:" <<
                    QSerialPortInfo::availablePorts().length();
        foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
        {
            qDebug() <<"Has vendor ID: " << serialPortInfo.hasVendorIdentifier();
            if(serialPortInfo.hasVendorIdentifier())
            {
                qDebug() <<"Vendor ID: " << serialPortInfo.vendorIdentifier();
            }
            qDebug() << "Has product ID: " << serialPortInfo.hasProductIdentifier();
            if(serialPortInfo.hasProductIdentifier())
            {
                qDebug() << "Product ID: " << serialPortInfo.productIdentifier();
            }
        }
    */

        foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
        {
            if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier())
            {
                if(serialPortInfo.vendorIdentifier()==arduino_uno_vendor_id)
                {
                    if(serialPortInfo.productIdentifier() == arduino_uno_product_id)
                    {
                        arduino_port_name = serialPortInfo.portName();
                        arduino_is_available = true;
                    }
                }
            }
            if(arduino_is_available)
            {
                //abri e configurar o serial
                arduino->setPortName(arduino_port_name);
                arduino->open(QSerialPort::ReadOnly);
                arduino->setBaudRate(QSerialPort::Baud9600);
                arduino->setDataBits(QSerialPort::Data8);
                arduino->setParity(QSerialPort::NoParity);
                arduino->setStopBits(QSerialPort::OneStop);
                arduino->setFlowControl(QSerialPort::NoFlowControl);
                QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(readSerial()));
            }
            else
            {
                //informar error
                QMessageBox::warning(this, "Port Error", "Arduino não conectado a porta");

            }
        }

}

Dialog::~Dialog()
{
    if(arduino->isOpen())
    {
        arduino->close();
    }
    delete ui;
}

void Dialog::readSerial()
{
    QString temp = arduino->readAll();
    qDebug() << temp;
    Dialog::updateTemperature(temp);
}
void Dialog::updateTemperature(QString valortemp)
{
    ui->Lcd->display(valortemp);
}
