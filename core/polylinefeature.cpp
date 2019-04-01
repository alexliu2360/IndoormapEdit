#include "polylinefeature.h"
#include <QJsonArray>
#include <QDateTime>

PolylineFeature::PolylineFeature(QGraphicsItem *parent) :
    QGraphicsObject(parent), m_type("0")
{
    generateId();
}

PolylineFeature::PolylineFeature(const QString &name, QGraphicsItem *parent) :
    QGraphicsObject(parent), m_type("0")
{
    generateId();
    setObjectName(name);
}

const QString &PolylineFeature::brief() const
{
    return m_brief;
}

int PolylineFeature::generateId(){
    //利用时间生成6位id, 小概率生成同样id...
    m_id = QDateTime::currentDateTime().toTime_t() % 1000000 +  qrand()% 100000 + 1000000;
    return m_id;
}

void PolylineFeature::setBrief(const QString & brief)
{
    if(m_brief == brief)
        return;
    m_brief = brief;
    emit briefChanged(m_brief);
}

bool PolylineFeature::isClassOf(const QString &className) const {
    QString myClassName;
    myClassName = this->metaObject()->className();
    return (!myClassName.compare(className));
}
int PolylineFeature::id() const
{
    return m_id;
}

void PolylineFeature::setId(const int id)
{
    if(m_id == id)
        return;
    int oldid = m_id;
    m_id = id;
    emit idChanged(oldid, m_id);
}

const QString & PolylineFeature::enName() const
{
    return m_enName;
}

void PolylineFeature::setEnName(const QString & name){
    if( m_enName == name)
        return;
    m_enName = name;
    emit enNameChanged(m_enName);
}

const QPointF & PolylineFeature::center() const
{
    return m_center;
}

void PolylineFeature::setCenter(const QPointF & center)
{
    if(m_center == center)
        return;
    m_center = center;
    emit centerChanged(m_center);
}

const QString & PolylineFeature::type() {
    return m_type;
}

void PolylineFeature::setType(const QString & type){
    if(m_type == type)
        return;
    m_type = type;
    emit typeChanged(m_type);
}

void PolylineFeature::setParentFeature(PolylineFeature *feature) {
    setParent(feature);
    setParentItem(feature);
}

bool PolylineFeature::load(const QJsonObject &jsonObject)
{
    setObjectName( jsonObject["Name"].toString() );
    m_enName = jsonObject["Name_en"].toString();
    m_brief = jsonObject["Brief"].toString();
    const QJsonArray & jsonArray = jsonObject["Center"].toArray();
    if(jsonArray.size() == 2){
        m_center = QPointF(jsonArray[0].toDouble(), -jsonArray[1].toDouble());
    }
    return true;
}

bool PolylineFeature::save(QJsonObject &jsonObject) const
{
    jsonObject["Name"] = objectName();
    jsonObject["Name_en"] = m_enName;
    jsonObject["Brief"] = m_brief;
    return true;
}

QRectF PolylineFeature::boundingRect() const
{
    return QRectF(m_center, m_center);
}

void PolylineFeature::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

void PolylineFeature::transformFeature(const QMatrix &matrix){
    m_center = matrix.map(m_center);
    emit centerChanged(m_center);
}
