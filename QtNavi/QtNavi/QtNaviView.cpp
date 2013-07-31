#include "QtNaviView.h"
//#include "FlickView.h"
#include <QGraphicsPixmapItem>
//#include "BaseItem.h"
//#include "ItemPage.h"
//#include "Config.h"

QtNaviView::QtNaviView(QWidget *parent)
	: QGraphicsView(parent)
{
	this->setWindowFlags(Qt::FramelessWindowHint);

	//this->setFixedSize(800,480);
	setTransformationAnchor(QGraphicsView::AnchorViewCenter);
	setResizeAnchor(QGraphicsView::AnchorUnderMouse);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //TODO: always on when debug.
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	QGraphicsScene *scene = new QGraphicsScene(this);
	//scene->setBackgroundBrush(QPixmap(":/Resources/bg_mainwnd.bmp"));
	//scene->setItemIndexMethod(QGraphicsScene::NoIndex);
	//scene->addItem(pad);
	scene->setSceneRect(0, 0, 800, 480);
	setScene(scene);
	

	//FlickView * pView = new FlickView();
	//scene->addItem(pView);



	//scene->addItem(item1);

	//this->installEventFilter(item);
}

void QtNaviView::mousePressEvent(QMouseEvent *event)
{
	return QGraphicsView::mousePressEvent(event);
}

void QtNaviView::mouseMoveEvent(QMouseEvent *event)
{
	return QGraphicsView::mouseMoveEvent(event);
}

// void QtNaviView::mouseReleaseEvent(QMouseEvent *event)
// {
// 	return QGraphicsView::mouseReleaseEvent(event);
// }



QtNaviView::~QtNaviView()
{

}
