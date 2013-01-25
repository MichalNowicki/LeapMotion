#ifndef _dela
#define _dela

volatile unsigned long TimeTick;

///
/// Funkcja opozniajaca o wielokrotnosc 10ms podana jako unsigned long tick
///
void Delay (unsigned long tick)
{
    unsigned long timetick;

    timetick = TimeTick;
    while ((TimeTick - timetick) < tick);
}

#endif
