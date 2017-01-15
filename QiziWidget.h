#ifndef QIZIWIDGET_H
#define QIZIWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include "Common.h"

class QiziWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QiziWidget(QWidget *parent, Qizi qizi);
    ~QiziWidget();

protected:
	virtual void paintEvent(QPaintEvent* event);

protected:
	QPixmap m_qiziPixmap;
};

#endif // QIZIWIDGET_H
