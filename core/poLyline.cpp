#include "polyline.h"
#include "polylinefeature.h"
#include "../gui/documentview.h"
#include <QPainter>
#include <QApplication>
#include <QGraphicsTextItem>
#include <QStyleOptionGraphicsItem>
#pragma execution_character_set("utf-8")

PolyLine::PolyLine(PolygonFeature &polygon):PolylineFeature(parent){

}
PolyLine::PolyLine( const QString & name, const QPolygon& poly):PolylineFeature(parent){

}

void PolyLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    Q_UNUSED(widget);

    //if selected
    QColor lineColor = (option->state & QStyle::State_Selected) ? m_color.darker(150) : m_color;

//    painter->setBrush(lineColor);
//    painter->setPen(QPen(borderColor, 1));
//    painter->drawPolygon(m_outline);

//    if(DocumentView::viewStyle() & DocumentView::StyleShowDirection && m_frontAngle != 0){
//        painter->setPen(QPen(QColor(255, 0, 0), 2));
//        painter->drawLine(0,0,2000,2000*tan(m_frontAngle));
//    }
}



bool PolyLine::load(const QJsonObject & jsonObject){

}
bool PolyLine::save(QJsonObject &jsonObject){

}

QPainterPath PolyLine::shape() const{

}

void PolyLine::setStartPoint(){

}
void PolyLine::setEndPoint(){

}
