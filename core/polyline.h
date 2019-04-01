#ifndef POLYLINE_H
#define POLYLINE_H

#include "polygonfeature.h"
#include "polylinefeature.h"
#include <QHash>
#include <QString>
#include <QJsonObject>
#include <QStyleOptionGraphicsItem>
class QGraphicsTextItem;
class PolyLine : public PolylineFeature
{
    Q_OBJECT
public:
    PolyLine(QGraphicsItem *parent = 0);
    PolyLine(const QString & name, QGraphicsItem *parent);
    
    //QGraphicsItem functions
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    bool load(const QJsonObject & jsonObject);
    bool save(QJsonObject &jsonObject);

    void setStartPoint();
    void setEndPoint();
private:
    QString m_startPoint;
    QString m_endPoint;
    QColor m_color;
    uint32_t m_distance;
    int m_id;
};

#endif // POLYLINE_H
