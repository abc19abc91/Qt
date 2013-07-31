#include "FlickView.h"
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include "ItemPage.h"
#include <QPropertyAnimation>
#include <QPainter>

FlickView::FlickView(QGraphicsItem *parent )
	: QGraphicsObject(parent)
	,m_nRowCount(0)
	,m_nColCount(0)
	,m_pAnimPage(NULL)
	,m_bPressed(false)
	,m_bIsMoving(false)
	,m_nMinPageDis(0)
	//,m_nPageCount(0)
	,m_nPageWidth(0)
	,m_nPageIndex(0)
	,m_nPageDuration(750)
{

}

FlickView::~FlickView()
{

}

void FlickView::setPixmap(const QPixmap &pixmap)
{
	m_Pixmap = pixmap;
	update();
}

void FlickView::paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	if (!m_Pixmap.isNull()) {
		//painter->scale(1.95, 1.95);
		painter->drawPixmap(0 - this->pos().x(), 0, m_Pixmap);
	}
}


QRectF FlickView::boundingRect() const 
{
  	return QRectF(0 - this->pos().x(), 0, 800, 480);
}

void FlickView::addItemPage(ItemPage * pItemPage)
{
	if (!pItemPage)
	{
		return;
	}
	
	pItemPage->setPageIndex(m_vItemPage.count());
	pItemPage->setPos(m_vItemPage.count() * m_nPageWidth, 0);
	pItemPage->setParentItem(this);
	m_vItemPage.append(pItemPage);
	update();
}

void FlickView::setMinMoveDis(int nDistance)
{
	m_nMinPageDis = nDistance;
}

void FlickView::setPageDuration(int nDuration)
{
	m_nPageDuration = nDuration;
}

int FlickView::rowCount() const
{
	return m_nRowCount;
}

void FlickView::setRowCount(const int& nRowCount)
{
	m_nRowCount = nRowCount;
}

int FlickView::colCount() const
{
	return m_nColCount;
}

void FlickView::setColCount(const int& nColCount)
{
	m_nColCount = nColCount;
}

void FlickView::setPageWidth(int nWidth)
{
	m_nPageWidth = nWidth;
}


void FlickView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
 	if (m_pAnimPage && QAbstractAnimation::Running == m_pAnimPage->state()) {
 		m_pAnimPage->stop();
 		m_bIsMoving = true;
 	}
 	m_bPressed = true;
 	m_MousePos = event->pos();
//	return QGraphicsWidget::mousePressEvent(event);
}

void FlickView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if (!m_bPressed )
	{
		return ;
	}

	if (!m_bIsMoving )
	{
		if (qAbs(event->pos().x() - m_MousePos.x()) >= m_nMinPageDis)
		{
			m_bIsMoving = true;
			m_MousePos = event->pos();
		}
		return ;
	}

	int distance = 0;
	if (isMoveAble(event->pos().toPoint(), distance)) 
	{
		QPointF delta = event->pos() - m_MousePos;
		this->setPos(this->pos().x()+ distance,this->pos().y());
		// 		QVector <ItemPage*> *itemPages = UiManager::instance()->GetItemPage();
		// 		for (int i = 0; i < itemPages->size(); ++i) 
		// 		{
		// 			itemPages->at(i)->setPos(itemPages->at(i)->pos().x()+ distance, itemPages->at(i)->pos().y());					
		// 		}
		m_MousePos = event->pos();
		//event->accept();
		return;
	}


}

void FlickView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if (m_bIsMoving)
	{
		startAnimation();
	}
	m_bIsMoving = false;
	m_bPressed = false;
	//return QGraphicsWidget::mouseReleaseEvent(event);
}

bool FlickView::isMoveAble(QPoint point, int &distance)
{

	if (point.x() > m_MousePos.x())//向右移动
	{
		if (this->pos().x() < 0)
		{
			distance = qMin(point.x() - m_MousePos.x(), 0 - this->pos().x());
			return true;
		}
		else
			return false;
	}
	else
	{
		if (this->pos().x() > 0 - (m_vItemPage.count() - 1) * m_nPageWidth)
		{
			distance = 0 - qMin(m_MousePos.x() - point.x(), this->pos().x() + m_vItemPage.count() * m_nPageWidth);
			return true;
		}
		else
			return false;
	}
}

void FlickView::startAnimation()
{

	int xPos = this->pos().x();
	int distance = xPos - ( 0 -m_nPageIndex ) * m_nPageWidth;
	//向右移动了
	if (distance > 0 )
	{
		//移动到页末
		if (distance >= m_nMinPageDis)
		{
			distance = m_nPageWidth - distance;
			--m_nPageIndex;
		}
		else  //移动回页首
			distance = 0 - distance;
	}
	else//向左移动了
	{
		//移动回页末
		if (0 - distance >= m_nMinPageDis)
		{
			distance = 0 - distance - m_nPageWidth;
			++m_nPageIndex;
		}
		else  //移动回页首
			distance = 0 - distance;
	}

	if (!m_pAnimPage)
	{
		m_pAnimPage = new QPropertyAnimation(this, "pos", this);
		m_pAnimPage->setDuration(m_nPageDuration );
		m_pAnimPage->setEasingCurve(QEasingCurve::OutQuad);
	}
	m_pAnimPage->setStartValue(this->pos());
	m_pAnimPage->setEndValue(QPointF(this->pos().x() + distance, this->pos().y()));
	m_pAnimPage->start();

}
