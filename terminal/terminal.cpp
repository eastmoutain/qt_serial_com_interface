#include "terminal.h"
#include <QRegExpValidator>
#include <QMessageBox>
#include <QColor>

terminal::terminal(QSerialPort *serial_port, QWidget *parent)
    : QDialog(parent),
      port(serial_port),
      standardOutput(stdout)
{
    baudRateIsSet = 0;
    serialPortNameIsSet = 0;
    QGridLayout *mainLayout = new QGridLayout(this);
    baudRateLabel = new QLabel(tr("Baud Rate"),this);
    baudRateCombo = new QComboBox;
    baudRateCombo->insertItem(0,"115200");
    baudRateCombo->insertItem(0,"38400");
    baudRateCombo->insertItem(0,"9600");
    serialPortNameLabel = new QLabel(tr("serial Port Name"),this);
    serialPortNameCombo = new QComboBox;
    serialPortNameCombo->insertItem(0,"ttyUSB0");
    serialPortNameCombo->insertItem(0,"ttyUSB1");

    connectBtn = new QPushButton(tr("connect"),this);
    disconnectBtn = new QPushButton(tr("disconnect"),this);
    disconnectBtn->hide();
    //connectBtn->hide();
    text = new QTextEdit();
    text->setReadOnly(true);
    //text->setTextBackgroundColor(QColor(0,0,255,127));
    mainLayout->addWidget(serialPortNameLabel,0,0);
    mainLayout->addWidget(serialPortNameCombo,0,1);
    mainLayout->addWidget(baudRateLabel,1,0);
    mainLayout->addWidget(baudRateCombo,1,1);
    mainLayout->addWidget(connectBtn,0,2);
    mainLayout->addWidget(disconnectBtn,1,2);
    mainLayout->addWidget(text,2,0,2,3);
    resize(600,450);

    connect(connectBtn,SIGNAL(clicked()),this, SLOT(configSerialPort()));
    connect(disconnectBtn,SIGNAL(clicked()),this, SLOT(disconnectSerialPort()));
    connect(port,SIGNAL(readyRead()),this,SLOT(showText()));
    connect(baudRateCombo,SIGNAL(currentIndexChanged(int)),this,\
            SLOT(baudRateComboIndexChanged(int)));
    connect(serialPortNameCombo,SIGNAL(currentIndexChanged(int)),this,\
            SLOT(serialPortNameComboIndexChanged(int)));

   // connect(text,SIGNAL())



    //connect(baudRateLine,SIGNAL(activated(int)), this, SLOT(showBtn()));

    /*
     * QRegExp regExpNameLine = "[A-Z]{0,6}[0-9]+";
     * QRegExp regExpbaudRateLine = "[0-9]*";
     * baudRateLine->setValidator(new QRegExpValidator(regExpNameLine, this));
     * baudRateLine->setValidator(new QRegExpValidator(regExpbaudRateLine, this));
     */
}

terminal::~terminal()
{

}

void terminal::configSerialPort()
{

    if(serialPortNameIsSet == 0)
    {
        portName = serialPortNameCombo->itemText(serialPortNameCombo->count()-1);
        //standardOutput<<"port name :"<<portName << endl;
    }
    if(baudRateIsSet == 0)
    {
        baudRate = baudRateCombo->itemText(baudRateCombo->count()-1).toInt();
        //standardOutput<<"baud rate :"<<baudRate << endl;
    }

    port->setBaudRate(baudRate);
    port->setPortName(portName);

    if (!port->open(QIODevice::ReadOnly)) {
        standardOutput << QObject::tr("Failed to open port %1, error: %2")\
                          .arg(portName).\
                          arg(port->error())\
                       << endl;
        return;
    }
    disconnectBtn->show();
    standardOutput << "+--------------------------+" << endl;
    standardOutput << "+   serial port is alive." << endl;
    standardOutput<<"+   baud: "<< baudRate << endl;
    standardOutput<<"+   port: "<< portName << endl;
    standardOutput << "+--------------------------+" << endl;
}
void terminal::disconnectSerialPort()
{
   port->close();
   disconnectBtn->hide();
   standardOutput << "+--------------------------+" << endl;
   standardOutput << "+   serial port is closed" << endl;
   standardOutput << "+--------------------------+" << endl;
}

void terminal::showBtn()
{

}

void terminal::showText()
{
    QByteArray str;
    text->moveCursor(QTextCursor::End,QTextCursor::MoveAnchor);
    str = port->readAll();
    text->insertPlainText(str);
    text->moveCursor(QTextCursor::End,QTextCursor::MoveAnchor);

}

void terminal::baudRateComboIndexChanged(int index)
{
    baudRate = baudRateCombo->itemText(index).toInt();
/*    QMessageBox::information(this,tr("baudRate Changed"), \
                             tr("baudRate:%1").arg(baudRate));
*/
    baudRateIsSet = 1;
}
void terminal::serialPortNameComboIndexChanged(int index)
{

    portName = serialPortNameCombo->itemText(index);
/*    QMessageBox::information(this,tr("serialPortName Changed"), \
                             tr("serialPortName:%1").arg(portName));
*/
   serialPortNameIsSet = 1;
}
