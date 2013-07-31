#ifndef ITEMPAGE_H
#define ITEMPAGE_H

#include <QGraphicsItemGroup>
class BaseItem;


class ItemPage : public QGraphicsItemGroup
{
	//Q_OBJECT

public:
	ItemPage(QGraphicsItem *parent = 0);
	virtual  ~ItemPage();
	void setPageIndex(const int& nIndex);
	bool addBaseItem(BaseItem * pItem);

	void setContentsMargins ( qreal left, qreal top, qreal right, qreal bottom );

	int rowCount() const;
	void setRowCount(const int& nRowCount);

	int colCount() const;
	void setColCount(const int& nColCount);

	bool resetItemGrid();

	void setItemWidth(int nWidth);
	void setItemHeight(int nHeight);

	void setPageWidth(int nWidth);
	void setPageHeight(int nHeight);

	//Q_PROPERTY(int rowCount READ rowCount WRITE setRowCount)

protected:


 	void mousePressEvent(QGraphicsSceneMouseEvent *event)
 	{
 		QGraphicsItemGroup::mousePressEvent(event);
 
 	}

	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
	{
		QGraphicsItemGroup::mouseReleaseEvent(event);
	}

	QRectF boundingRect() const
	{
		return QRectF(0, 0, 0, 0);
	}

	//virtual QRectF boundingRect ();
private:
 	int m_nPageIndex;
 	int m_nRowCount;
	int m_nColCount;
	QVector<QVector<BaseItem *> > m_vItemGrid;

	int m_nMarginsLeft;
	int m_nMarginsTop;
	int m_nMarginsRight;
	int m_nMarginsBottom;

	int m_nItemWidth;
	int m_nItemHeight;

	int m_nPageWidth;
	int m_nPageHeight;
};


#endif // ITEMPAGE_H
