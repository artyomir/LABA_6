#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QPainter>
#include <QDebug>

class Bullet: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Bullet(QPointF start, QPointF end, QGraphicsItem *hero, QObject *parent = 0);
    ~Bullet();
    void setCallbackFunc(void (*func) (QGraphicsItem * item));

signals:


public slots:

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void (*callbackFunc)(QGraphicsItem * item);

private:
    QTimer *timerBullet;    // Слот для обработки таймера пули
    QGraphicsItem *hero;

private slots:
    void slotTimerBullet(); // Слот для обработки полёта пули
};


#endif // BULLET_H
