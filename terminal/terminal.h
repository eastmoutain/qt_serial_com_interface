#ifndef TERMINAL_H
#define TERMINAL_H

#include <QDialog>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QtSerialPort/QSerialPort>
#include <QTextStream>
#include <QObject>
#include <QTimer>
#include <QString>
#include <QByteArray>
#include <QLabel>

#include <QtSerialPort/QSerialPort>

#include <QTextStream>
#include <QTimer>
#include <QByteArray>
#include <QObject>
#include <QComboBox>

QT_USE_NAMESPACE

QT_BEGIN_NAMESPACE

QT_END_NAMESPACE

class terminal : public QDialog
{
    Q_OBJECT

public:
    terminal(QSerialPort *serial_port, QWidget *parent = 0);
    ~terminal();
    int writeText(const QByteArray &array);

    void showBtn();
    void setSerialPortName(QString &portName);
public slots:
    void configSerialPort();
    void disconnectSerialPort();
    void showText();
    void baudRateComboIndexChanged(int);
    void serialPortNameComboIndexChanged(int);
private:
    QPushButton     *connectBtn;
    QPushButton *disconnectBtn;
    QComboBox   *baudRateCombo;
    QComboBox   *serialPortNameCombo;
    QSerialPort     *port;
    qint64          baudRate;
    QString         portName;
    qint8 baudRateIsSet;
    qint8 serialPortNameIsSet;
    QByteArray      writeData;
    QTextStream     standardOutput;
    QLabel  *baudRateLabel;
    QLabel  *serialPortNameLabel;
    QTextEdit *text;



};

#endif // TERMINAL_H
