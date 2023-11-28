#include "interaction.h"
#include <QDebug>
Interaction::Interaction(QObject *parent)
    : QObject{parent}
{



}

void Interaction::test_slot()
{

    controller.start();
}
