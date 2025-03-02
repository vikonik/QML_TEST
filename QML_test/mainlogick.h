#ifndef MAINLOGICK_H
#define MAINLOGICK_H

#include <QObject>
#include "debug.h"
#include "serial.h"

class MainLogick
{
public:
    MainLogick();

    Debug *debugWindow;
private:
 Serial *serial;
};

#endif // MAINLOGICK_H
