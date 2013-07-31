#include "BaseItem.h"
#include <QTimer>
#include <QGraphicsSceneMouseEvent>
//#include "Config.h"
#include <QDrag>
#include <QGraphicsScene>
#include <QMimeData>
#include <QPainter>

BaseItem::BaseItem( QGraphicsItem *parent )
	: QGraphicsObject(parent)
	,m_nRowIndex(0)
	,m_nColIndex(0)
{
	//m_Pixmap = pixmap;
	this->setAcceptDrops(true);
	m_pTimer = new QTimer(this);
	m_pTimer->setSingleShot(true);
	connect(m_pTimer, SIGNAL(timeout()), this, SLOT(onItemDrag()));
}

BaseItem::~BaseItem()
{

}

QPixmap BaseItem::pixmap() const
{
	return m_Pixmap;
}

void BaseItem::setPixmap(const QPixmap &pixmap)
{
	m_Pixmap = pixmap;
	update();
}

 QRectF BaseItem::boundingRect() const
 {
 	return QRectF(0, 0, 227, 185);
	 
 }

void BaseItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
						  QWidget *widget)
{
	if (!m_Pixmap.isNull()) {
		//painter->scale(1.95, 1.95);
		painter->drawPixmap(0, 0, m_Pixmap);
	}
}

void BaseItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if (!m_pTimer->isActive())
	{
		m_PointPressed = event->pos();
		m_pTimer->start(2000);
	}
	QGraphicsSceneMouseEvent  translatedEvent(event->type());
	translatedEvent.setPos(mapToItem(parentItem()->parentItem(), event->pos()).toPoint());
	scene()->sendEvent(parentItem()->parentItem(), &translatedEvent);

	//QGraphicsObject::mousePressEvent(event);

}

void BaseItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if (m_pTimer->isActive())
	{
		m_pTimer->stop();
	}

	QGraphicsSceneMouseEvent  translatedEvent(event->type());
	translatedEvent.setPos(mapToItem(parentItem()->parentItem(), event->pos()).toPoint());
	scene()->sendEvent(parentItem()->parentItem(), &translatedEvent);

	//QGraphicsObject::mouseMoveEvent(event);
}

void BaseItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
// 	if (Config::m_bIsDraging)
// 	{
// 		Config::m_bIsDraging =false;
// 		this->setZValue(0);
// 	}
	
	if (m_pTimer->isActive())
	{
		m_pTimer->stop();
	}

	QGraphicsSceneMouseEvent  translatedEvent(event->type());
	translatedEvent.setPos(mapToItem(parentItem()->parentItem(), event->pos()).toPoint());
	scene()->sendEvent(parentItem()->parentItem(), &translatedEvent);

	//QGraphicsObject::mouseReleaseEvent(event);

}


void BaseItem::onItemDrag()
{
	this->hide();
	QDrag* drag = new QDrag((QWidget*)this->scene()->views().at(0));  

	QMimeData* data = new QMimeData();  
	drag->setMimeData(data);  

	QPixmap pixmap(":/Resources/button/btn_navi_p.png");   
	QPainter painter(&pixmap);  

	drag->setPixmap(pixmap); //这里设置拖拽时跟随鼠标的图片  
	drag->setHotSpot(QPoint(15,15)); //设置跟随图片的中心点  

	drag->exec();

	delete drag;
	this->show();

	

}

int	BaseItem::rowIndex() const
{
	return m_nRowIndex;
}

void BaseItem::setRowIndex(const int& nIndex)
{
	m_nRowIndex = nIndex;
}

int	BaseItem::colIndex() const
{
	return m_nColIndex;
}

void BaseItem::setColIndex(const int& nIndex)
{
	m_nColIndex = nIndex;
}


#if 1
bool BaseItem::sceneEvent(QEvent *event)
{
	if (event->type() == QEvent::GraphicsSceneMousePress)
	{ mousePressEvent((QGraphicsSceneMouseEvent *)(event)); }

	else if (event->type() == QEvent::GraphicsSceneMouseRelease)
	{ mouseReleaseEvent((QGraphicsSceneMouseEvent *)(event)); }
	else if (event->type() == QEvent::GraphicsSceneMouseMove)
	{ mouseMoveEvent((QGraphicsSceneMouseEvent *)(event)); }

	event->setAccepted(true);
	return true;
}
#endif
