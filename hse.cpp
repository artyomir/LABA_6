#include "hse.h"
#include <math.h>
#include <QGraphicsScene>

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

static qreal normalizeAngle(qreal angle)
{
    while (angle < 0)
        angle += TwoPi;
    while (angle > TwoPi)
        angle -= TwoPi;
    return angle;
}

HSE::HSE(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    setRotation(0);      // Устанавливаем исходный разворот треугольника

    target = QPointF(0,0);  // Устанавливаем изначальное положение курсора
    shot = false;

    gameTimer = new QTimer();   // Инициализируем игровой таймер
    // Подключаем сигнал от таймера и слоту обработки игрового таймера
    connect(gameTimer, &QTimer::timeout, this, &HSE::slotGameTimer);
    gameTimer->start(10);   // Стартуем таймер

    bulletTimer = new QTimer(); // Инициализируем таймер создания пуль
    connect(bulletTimer, &QTimer::timeout, this, &HSE::slotBulletTimer);
    bulletTimer->start(1000/6); // Стреляем 6 раз в секунду
    target = QPointF(0,0);  // Устанавливаем изначальное положение курсора
    health = 15;
    maxHealth = health;
}

HSE::~HSE()
{

}

QRectF HSE::boundingRect() const
{
//    return QRectF(-100,-100,100,100);
    return QRectF(-15,-15,35,35);
}

void HSE::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    /* Отрисовка треугольника
     * */
    QPolygon polygon;
    polygon << QPoint(0,-15) << QPoint(10,15) << QPoint(-10,15);
    painter->setBrush(Qt::blue);
    painter->drawPolygon(polygon);

    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::green);
    painter->drawRect(-10,18, (int) 20  * health/maxHealth ,2);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void HSE::slotTarget(QPointF point)
{
    // Определяем расстояние до цели
    target = point;
    QLineF lineToTarget(QPointF(0, 0), mapFromScene(target));
    // Угол поворота в направлении к цели
    qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
    if (lineToTarget.dy() < 0)
        angleToTarget = TwoPi - angleToTarget;
    angleToTarget = normalizeAngle((Pi - angleToTarget) + Pi / 2);

    /* В Зависимости от того, слева или справа находится Цель от Героя,
     * устанавливаем направление поворота Героя в данном тике таймера
     * */
    if (angleToTarget >= 0 && angleToTarget < Pi) {
        // Rotate left
        setRotation(rotation() - angleToTarget * 180 /Pi);
    } else if (angleToTarget <= TwoPi && angleToTarget > Pi) {
        // Rotate right
        setRotation(rotation() + (angleToTarget - TwoPi )* (-180) /Pi);
    }
}

void HSE::slotGameTimer()
{    /** Перемещаем треугольник в зависимости от нажатых кнопок
     * */
    if(GetAsyncKeyState('A')){
        this->setX(this->x() - 1);
        /* Проверяем на столкновение,
         * если столкновение произошло,
         * то возвращаем героя обратно в исходную точку
         * */
        if(!scene()->collidingItems(this).isEmpty()){
            this->setX(this->x() + 1);
        }
    }
    if(GetAsyncKeyState('D')){
        this->setX(this->x() + 1);
        /* Проверяем на столкновение,
         * если столкновение произошло,
         * то возвращаем героя обратно в исходную точку
         * */
        if(!scene()->collidingItems(this).isEmpty()){
            this->setX(this->x() - 1);
        }
    }
    if(GetAsyncKeyState('W')){
        this->setY(this->y() - 1);
        /* Проверяем на столкновение,
         * если столкновение произошло,
         * то возвращаем героя обратно в исходную точку
         * */
        if(!scene()->collidingItems(this).isEmpty()){
            this->setY(this->y() + 1);
        }
    }
    if(GetAsyncKeyState('S')){
        this->setY(this->y() + 1);
        /* Проверяем на столкновение,
         * если столкновение произошло,
         * то возвращаем героя обратно в исходную точку
         * */
        if(!scene()->collidingItems(this).isEmpty()){
            this->setY(this->y() - 1);
        }
    }
    if(GetAsyncKeyState(VK_LEFT)){
        this->setX(this->x() - 1);
        /* Проверяем на столкновение,
         * если столкновение произошло,
         * то возвращаем героя обратно в исходную точку
         * */
        if(!scene()->collidingItems(this).isEmpty()){
            this->setX(this->x() + 1);
        }
    }
    if(GetAsyncKeyState(VK_RIGHT)){
        this->setX(this->x() + 1);
        /* Проверяем на столкновение,
         * если столкновение произошло,
         * то возвращаем героя обратно в исходную точку
         * */
        if(!scene()->collidingItems(this).isEmpty()){
            this->setX(this->x() - 1);
        }
    }
    if(GetAsyncKeyState(VK_UP)){
        this->setY(this->y() - 1);
        /* Проверяем на столкновение,
         * если столкновение произошло,
         * то возвращаем героя обратно в исходную точку
         * */
        if(!scene()->collidingItems(this).isEmpty()){
            this->setY(this->y() + 1);
        }
    }
    if(GetAsyncKeyState(VK_DOWN)){
        this->setY(this->y() + 1);
        /* Проверяем на столкновение,
         * если столкновение произошло,
         * то возвращаем героя обратно в исходную точку
         * */
        if(!scene()->collidingItems(this).isEmpty()){
            this->setY(this->y() - 1);
        }
    }
//    /* Перемещаем треугольник в зависимости от нажатых кнопок
//     * */

    /* Проверка выхода за границы поля
     * Если объект выходит за заданные границы, то возвращаем его назад
     * */
    if(this->x() - 30 < 0){
        this->setX(30);         // слева
    }
    if(this->x() + 30 > 500){
        this->setX(500 - 30);   // справа
    }

    if(this->y() - 30 < 0){
        this->setY(30);         // сверху
    }
    if(this->y() + 30 > 500){
        this->setY(500 - 30);   // снизу
    }

    QLineF lineToTarget(QPointF(0, 0), mapFromScene(target));
    // Угол поворота в направлении к цели
    qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
    if (lineToTarget.dy() < 0)
        angleToTarget = TwoPi - angleToTarget;
    angleToTarget = normalizeAngle((Pi - angleToTarget) + Pi / 2);

    /* В Зависимости от того, слева или справа находится Цель от Героя,
     * устанавливаем направление поворота Героя в данном тике таймера
     * */
    if (angleToTarget >= 0 && angleToTarget < Pi) {
        // Rotate left
        setRotation(rotation() - angleToTarget * 180 /Pi);
    } else if (angleToTarget <= TwoPi && angleToTarget > Pi) {
        // Rotate right
        setRotation(rotation() + (angleToTarget - TwoPi )* (-180) /Pi);
    }
}

void HSE::slotBulletTimer()
{
    // Если стрельба разрешена, то вызываем сигнал на создание пули
    if(shot) emit signalBullet(mapToScene(0,-25), target);
}

void HSE::slotShot(bool shot)
{
    this->shot = shot;  // Получаем разрешение или запрет на стрельбу
}

QPainterPath HSE::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void HSE::hit(int damage)
{
    health -= damage;   // Уменьшаем здоровье мишени
    this->update(QRectF(-15,-15,35,35));    // Перерисовываем мишень
    // Если здоровье закончилось, то инициируем смерть мишени
    if(health <= 0) this->deleteLater();
}
