#include "NaviBar.h"
#include <QPainter>

NaviBar::NaviBar(QGraphicsItem *parent)
	: QGraphicsObject(parent)
{

}

NaviBar::~NaviBar()
{

}

void NaviBar::setPixmap(const QPixmap &pixmap)
{
	m_Pixmap = pixmap;
	update();
}

QRectF NaviBar::boundingRect() const 
{
	return QRectF(0 , 0, 800, 33);
}

void NaviBar::paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	if (!m_Pixmap.isNull()) {
		//painter->scale(1.95, 1.95);
		painter->drawPixmap(0 - this->pos().x(), 0, m_Pixmap);
	}

	//painter->setFont(QFont(QString::fromUtf8("宋体"),50,-1,false));
	painter->drawText(0,0,211,30,Qt::AlignHCenter|Qt::AlignVCenter, tr("test"));
}
