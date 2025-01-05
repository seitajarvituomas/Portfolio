#include "qtimer.hh"

QTimer::QTimer()
{

}

void QTimer::timeout()
{
    seconds++;
    if (seconds >= 60) {
        seconds = 0;
        minutes++;
        if (minutes >= 60) {
            minutes = 0;
        }
    }
}
