#ifndef PolylineTool_H
#define PolylineTool_H


#include "abstracttool.h"

#include <core/polyline.h>
class PolylineTool : public AbstractTool
{
    Q_OBJECT
public:
    explicit PolylineTool(DocumentView* doc);

    virtual void mousePressEvent( QGraphicsSceneMouseEvent *event );
    virtual void mouseReleaseEvent( QGraphicsSceneMouseEvent *event );
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
private:
    bool m_start;
    bool m_isCreating;
    PolyLine * m_polyline;
protected:
    DocumentView* m_doc;
    QMenu* m_contextMenu;
};

#endif // PolylineTool_H
