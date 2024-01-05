#ifndef DICE_H
#define DICE_H

class dice : public QObject
{
    Q_OBJECT

public:
    explicit dice(QObject *parent = nullptr);
    ~dice();
    void updateImg();

    int value;

private slots:
    void increase();
    void decrease();

private:
    QImage* diceDisplayed;
};

#endif // DICE_H
