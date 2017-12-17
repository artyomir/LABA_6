#include "customescene.h"

CustomeScene::CustomeScene(QObject *parent) :
    QGraphicsScene()
{
    Q_UNUSED(parent);
}

CustomeScene::~CustomeScene()
{

}

void CustomeScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    emit signalTargetCoordinate(event->scenePos());
}

void CustomeScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit signalShot(true); // Когда клавиша мыши нажата, то можно стрелять
    Q_UNUSED(event);
}

void CustomeScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit signalShot(false); // Когда клавишу мыши отпустили, то стрелять нельзя
    Q_UNUSED(event);
}
