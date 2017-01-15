#include "QiziWidget.h"
#include <QPainter>

QiziWidget::QiziWidget(QWidget *parent, Qizi qizi) : QWidget(parent)
{
	if (qizi == BLACK_QIZI)
		m_qiziPixmap.load(":/res/black.png");
	else if (qizi == WHITE_QIZI)
		m_qiziPixmap.load(":/res/white.png");
}

QiziWidget::~QiziWidget()
{

}

void QiziWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.drawPixmap(rect(), m_qiziPixmap);

	QWidget::paintEvent(event);
}