#ifndef NAVIBAR_H
#define NAVIBAR_H

#include <QGraphicsObject>

class NaviBar : public QGraphicsObject
{
	Q_OBJECT
public:
	NaviBar(QGraphicsItem *parent = NULL);
	~NaviBar();

	void setPixmap(const QPixmap &pixmap);
protected:
	QRectF boundingRect() const ;
	void paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );

private:
	QPixmap		m_Pixmap;
};

#endif // NAVIBAR_H
