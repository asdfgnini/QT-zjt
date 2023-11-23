#include "interaction.h"

Interaction::Interaction(QObject *parent)
    : QObject{parent}
{

    controller.start();

}
