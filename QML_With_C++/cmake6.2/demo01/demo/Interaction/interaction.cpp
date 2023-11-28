#include "interaction.h"
#include <QDebug>
Interaction::Interaction(QObject *parent)
    : QObject{parent}
{
    controller.start();
}
void Interaction::test()
{
    qDebug() << "test";
}
