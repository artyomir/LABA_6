#ifndef HSE_H
#define HSE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPolygon>
#include <QTimer>
#include <QDebug>
#include <QCursor>

#include <windows.h>

class HSE: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit HSE(QObject *parent = 0);
    ~HSE();
    void hit(int damage);

signals:
    // Сигнал для создания пули с параметрами траектории
    void signalBullet(QPointF start, QPointF end);
public slots:
    // Слот для получения данных о положении курсора
    void slotTarget(QPointF point);
    void slotShot(bool shot);

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;

private slots:
    void slotGameTimer();   // Игровой слот
    void slotBulletTimer(); // Слот проверки пули

private:
    QTimer *gameTimer;      // Игровой таймер
    QPointF target;         // Положение курсора
    bool shot;              // Переменная состояния стрельбы
    QTimer *bulletTimer;    // Таймер пули
    int health;
    int maxHealth;
};

#endif // HSE_H
