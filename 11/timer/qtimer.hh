#ifndef QTIMER_HH
#define QTIMER_HH


class QTimer
{
public:
    QTimer();

    void timeout();

private:
    int seconds = 0;
    int minutes = 0;

};


#endif // QTIMER_HH
