#ifndef BASEITEM_H
#define BASEITEM_H

#include <QGraphicsObject>
#include <QEvent>

class BaseItem : public QGraphicsObject
{
	Q_OBJECT

public:
	BaseItem(QGraphicsItem *parent = 0);
	~BaseItem();

	QPixmap pixmap() const;
	void	setPixmap(const QPixmap &pixmap);

	int		rowIndex() const;
	void	setRowIndex(const int& nIndex);
	int		colIndex() const;
	void	setColIndex(const int& nIndex);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

	 QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
#if 1
	//如果将QGraphicsItem加入到QGraphicsItemGroup中，会导致QGraphicsItem收不到鼠标消息，重载这个函数后正常
	bool sceneEvent(QEvent *event);
#endif
	//QRectF boundingRect() const;
private:
	QTimer *	m_pTimer;
	QPointF		m_PointPressed;

	QPixmap		m_Pixmap;

	int			m_nRowIndex;
	int			m_nColIndex;
private slots:
	void onItemDrag();

	
	
};

#endif // BASEITEM_H
