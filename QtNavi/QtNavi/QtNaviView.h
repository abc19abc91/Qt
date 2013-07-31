#ifndef QTNAVI_H
#define QTNAVI_H

#include <QGraphicsView>


class QtNaviView : public QGraphicsView
{
	Q_OBJECT

public:
	QtNaviView(QWidget *parent = 0);
	~QtNaviView();


protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	//void mouseReleaseEvent(QMouseEvent *event);
private:

};

#endif // QTNAVI_H
