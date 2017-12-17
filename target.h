#ifndef TARGET_H
#define TARGET_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QTimer>

class Target: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Target(QObject *parent = 0);
    ~Target();
    /* Функция по нанесению урона,
     * величина урона передаётся в качестве аргумента функции
     * */
    void hit(int damage);

signals:
    void signalBullet(QPointF start, QPointF end);

public slots:
    // Слот для получения данных о положении курсора
    void slotTargetHSE(QPointF point);
    // слот для обработки разрешения стрельбы
    void slotShot(bool shot);

private slots:
    void slotBulletTimer();
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    int health;         // Текущий запас здоровья мишени
    int maxHealth;      // Максимальный запас здоровья мишени
    bool shot;              // Переменная состояния стрельбы
    QTimer *bulletTimer;    // Таймер пули
    QPointF targetHSE;         // Положение курсора
};

#endif // TARGET_H
