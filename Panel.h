#ifndef PANEL_H
#define PANEL_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QStack>
#include "Controller.h"
#include "QiziWidget.h"

class Panel : public QWidget
{
    Q_OBJECT
public:
	explicit Panel(QWidget *parent = 0);
    ~Panel();

	struct StepRecord
	{
		Step step;
		QiziWidget* qiziWidget;
	};
    
	void create(QRect validRect, int row, int column);
	void reset();
	void start(Qizi qizi, bool firstDrop);
	Qizi myQizi();
	Qizi otherQizi();
	void regret(Qizi qizi);

protected:
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void paintEvent(QPaintEvent* event);
    
    Pos pointToPos(const QPoint& pt);
	QPoint posToPoint(const Pos& pos);

signals:
	void dropMine(Step step);
	void win(Qizi qizi);

public slots:
    void dropQizi(Step step);
    
protected:
    QRect m_validRect;
    int m_row;
    int m_column;
    
    Controller* m_gameCtrl;
	QStack<StepRecord> m_stepRecord;
};

#endif // PANEL_H
