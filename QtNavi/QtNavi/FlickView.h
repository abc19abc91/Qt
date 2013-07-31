#ifndef FLICKVIEW_H
#define FLICKVIEW_H

#include <QGraphicsObject>
class ItemPage;
class QPropertyAnimation;
class QGraphicsSceneMouseEvent;

class FlickView :public QGraphicsObject
{
	Q_OBJECT

public:
	FlickView(QGraphicsItem *parent = 0);
	~FlickView();

	void setPixmap(const QPixmap &pixmap);
	void addItemPage(ItemPage * pItemPage);

	int rowCount() const;
	void setRowCount(const int& nRowCount);

	int colCount() const;
	void setColCount(const int& nColCount);

	void setMinMoveDis(int nDistance);
	void setPageDuration(int nDuration);
	void setPageWidth(int nWidth);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

	QRectF boundingRect() const ;
	void paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );



private:
	QVector<ItemPage * > m_vItemPage;
	QPixmap		m_Pixmap;

	int m_nRowCount;
	int m_nColCount;

	QPropertyAnimation *m_pAnimPage;
	bool m_bPressed;
	QPointF m_MousePos;
	bool m_bIsMoving;
	int m_nMinPageDis;
	int m_nPageDuration;
	int m_nPageIndex;
	//int m_nPageCount;
	int m_nPageWidth;

private:
	void startAnimation();
	bool isMoveAble(QPoint point, int &distance);
};

#endif // FLICKVIEW_H
