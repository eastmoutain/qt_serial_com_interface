#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>

class serial : public QObject
{
    Q_OBJECT
public:
    explicit serial(QObject *parent = 0);

signals:

public slots:

};

#endif // SERIAL_H
