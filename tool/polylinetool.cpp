#include "polylinetool.h"
#include "polygontool.h"
#include "../gui/documentview.h"
#include "../core/room.h"
#include "../core/building.h"
#include "../core/scene.h"
#include <QGraphicsSceneEvent>
#include <QDebug>
#pragma execution_character_set("utf-8")

PolylineTool::PolylineTool(DocumentView *doc) :
    AbstractTool(doc), m_start(true), m_isCreating(false), m_polyline(NULL)
{
}

void PolylineTool::mousePressEvent( QGraphicsSceneMouseEvent *event ){

}
void PolylineTool::mouseReleaseEvent( QGraphicsSceneMouseEvent *event ){
//    qDebug()<<"PolygonTool:"<<event->scenePos().rx()<<","<<event->scenePos().ry()<<endl;
    if(event->button() == Qt::LeftButton) {//left button down
        if(m_start){ //start creating
            m_polyline = m_doc->scene()->createPolygonByContext();
            m_start = false;
            m_isCreating = true;
            m_doc->scene()->clearSelection();

            m_polyline->addPoint(event->scenePos().toPoint());
        }
        m_polyline->addPoint(event->scenePos().toPoint());

        //redraw
        m_polyline->update(m_polyline->boundingRect());
    }else if(event->button() == Qt::RightButton){//right button down, finish
        if(m_isCreating){
            //remove the last point
            m_polyline->removePoint(m_polyline->PointNum() - 1); //pop the end point

            if(m_polyline->PointNum() < 3){
                m_doc->scene()->deletePolygonByContext(m_polyline);
            }else{
                m_polyline->computeCenter();
                m_polyline->computeArea();

                if(m_polyline->isClassOf("FuncArea")){
                    m_polyline->setObjectName(tr("未命名"));
                }

                //selection
                m_doc->scene()->clearSelection();
                m_polyline->setSelected(true);
                m_doc->scene()->setSelectedLayer(m_polyline);
            }
            m_start = true;
            m_isCreating = false;
            //redraw
            m_doc->scene()->update();
            event->accept();
        }
    }
}
void PolylineTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(m_isCreating){
        m_doc->scene()->update();
        m_polyline->movePointTo(m_polyline->PointNum()-1, event->scenePos().toPoint());
    }
}
