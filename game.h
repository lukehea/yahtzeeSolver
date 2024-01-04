#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QVector>

class game : public QObject
{
    Q_OBJECT
public:
    explicit game(QObject *parent = nullptr);

signals:

private:
    QVector<int> scores;

};

#endif // GAME_H
