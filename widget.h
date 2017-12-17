#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include "bullet.h"
#include "target.h"

#include "customescene.h"
#include "HSE.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    CustomeScene  *scene;    // Объявляем графическую сцену
    HSE *triangle;     // Объявляем треугольник
    QTimer *timerTarget;        // Таймер для создания мишеней
    static QList<QGraphicsItem *> targets;  // Список мишеней

    static void slotHitTarget(QGraphicsItem *item); // CallBack Функция

private slots:
    void slotCreateTarget(); // Слот для создания мишеней
    void slotBullet(QPointF start, QPointF end);
};

#endif // WIDGET_H
