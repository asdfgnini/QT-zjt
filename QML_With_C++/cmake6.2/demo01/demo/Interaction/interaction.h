#ifndef INTERACTION_H
#define INTERACTION_H

#include <QObject>

#include "C++/worker.h"

class Interaction : public QObject
{
    Q_OBJECT
public:
    explicit Interaction(QObject *parent = nullptr);
    Q_INVOKABLE void test();
private:
    Controller controller;

signals:

};

#endif // INTERACTION_H
