#include "BaseItem.h"
#include <QTimer>
#include <QGraphicsSceneMouseEvent>
//#include "Config.h"
#include <QDrag>
#include <QGraphicsScene>
#include <QMimeData>
#include <QPainter>
#include <QPropertyAnimation>

BaseItem * BaseItem::m_pItemSource = NULL;

BaseItem::BaseItem( QGraphicsItem *parent, int nIndex )
	: QGraphicsObject(parent)
	,m_nIndex(nIndex)
	,m_nRowIndex(0)
	,m_nColIndex(0)
	,m_bIsMoved(false)
{
	//m_Pixmap = pixmap;
	this->setAcceptDrops(true);

	m_pTimer = new QTimer(this);
	m_pTimer->setSingleShot(true);
	connect(m_pTimer, SIGNAL(timeout()), this, SLOT(onItemDrag()));

	m_pAnimItem = new QPropertyAnimation(this, "pos", this);
	m_pAnimItem->setDuration(750 );
	m_pAnimItem->setEasingCurve(QEasingCurve::OutQuad);
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



}


void BaseItem::onItemDrag()
{
	this->hide();
	QDrag* drag = new QDrag((QWidget*)this->scene()->views().at(0));  

	BaseItem::m_pItemSource = this;

	QMimeData* data = new QMimeData();  
	drag->setMimeData(data);  

	//QPixmap pixmap(m_Pixmap);   
	//QPainter painter(&pixmap);  
	
	QPixmap pixmap = m_Pixmap.scaled(m_Pixmap.width() * 1.2, m_Pixmap.height() * 1.2);

	QPixmap * q=new QPixmap(pixmap.size());
	q->fill(QColor(100,100,100,100));
	pixmap.setAlphaChannel(*q);


	drag->setPixmap(pixmap); //这里设置拖拽时跟随鼠标的图片  
	drag->setHotSpot(m_PointPressed.toPoint()); //设置跟随图片的中心点  

	drag->exec();

	delete drag;
	this->show();

	

}

void BaseItem::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{

//	BaseItem * p = qobject_cast<BaseItem*>(event->source());

	if(QAbstractAnimation::Stopped == m_pAnimItem->state())
	{
		startAnimation(BaseItem::m_pItemSource);
	}
	
		
}

void BaseItem::startAnimation(BaseItem * pItem)
{
	//QPointF pointTemp = this->pos();

	
	
	
	m_pAnimItem->setStartValue(this->pos());
	m_pAnimItem->setEndValue(pItem->pos());
	pItem->setPos(this->pos());
	m_pAnimItem->start();

	
	int rowIndex = this->rowIndex();
	int colIndex = this->colIndex();
	this->setRowIndex(pItem->rowIndex());
	this->setColIndex(pItem->colIndex());
	pItem->setRowIndex(rowIndex);
	pItem->setColIndex(colIndex);
	this->m_bIsMoved = true;
	pItem->m_bIsMoved = true;

}


//! [1]

//! [2]
void BaseItem::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);

}
//! [2]

//! [3]
void BaseItem::dropEvent(QGraphicsSceneDragDropEvent *event)
{

}
//! [3]

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
	else if (event->type() == QEvent::GraphicsSceneDragEnter)
	{ dragEnterEvent((QGraphicsSceneDragDropEvent *)(event)); }
	else if (event->type() == QEvent::GraphicsSceneDragLeave)
	{ dragLeaveEvent((QGraphicsSceneDragDropEvent *)(event)); }
	else if (event->type() == QEvent::GraphicsSceneDrop)
	{ dropEvent((QGraphicsSceneDragDropEvent *)(event)); }

	event->setAccepted(true);
	return true;
}
#endif
