#ifndef INTERACTION_H
#define INTERACTION_H

#include <QObject>
#include "controller.h"


class Interaction : public QObject
{
    Q_OBJECT
public:
    explicit Interaction(QObject *parent = nullptr);
    Q_INVOKABLE void test_slot();
private:
    Controller controller;

private slots:


signals:

};

#endif // INTERACTION_H
