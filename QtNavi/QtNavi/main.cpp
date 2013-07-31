#include "qtnaviView.h"
#include <QtGui/QApplication>
#include "Config.h"
#include "UiManager.h"
#include <QTextCodec>
#include <QTranslator>

#include "BaseItem.h"

int main(int argc, char *argv[])
{
	QTextCodec *codec = QTextCodec::codecForName("UTF-8");
	QTextCodec::setCodecForLocale(codec);
	QTextCodec::setCodecForCStrings(codec);
	QTextCodec::setCodecForTr(codec);

	QApplication a(argc, argv);

	QTranslator translator;
	bool bret = translator.load("qtnavi_zh.qm");
	a.installTranslator(&translator);


	QtNaviView w;
	//w.setGeometry(0, 0, 800, 480);
	Config::LoadConfig();
	UiManager::instance()->init(&w);
	w.show();



	

	return a.exec();
}
