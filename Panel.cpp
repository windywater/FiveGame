#include "Panel.h"
#include <QPainter>

Panel::Panel(QWidget *parent) : QWidget(parent)
{
	m_gameCtrl = NULL;
}

Panel::~Panel()
{
    
}

void Panel::create(QRect validRect, int row, int column)
{
	m_validRect = validRect;
	m_row = row;
	m_column = column;

	if (m_gameCtrl)
		delete m_gameCtrl;
	
	m_gameCtrl = new Controller(this, m_row, m_column);
}

void Panel::reset()
{
	m_gameCtrl->reset();
	
	while (!m_stepRecord.empty())
	{
		delete m_stepRecord.top().qiziWidget;
		m_stepRecord.pop();
	}
}

void Panel::start(Qizi qizi, bool firstDrop)
{
	m_gameCtrl->start(qizi, firstDrop);
}

Qizi Panel::myQizi()
{
	return m_gameCtrl->myQizi();
}

Qizi Panel::otherQizi()
{
	return m_gameCtrl->otherQizi();
}

void Panel::mousePressEvent(QMouseEvent* event)
{
	if (!m_gameCtrl->isMyTurn())
		return;

    Pos pos = pointToPos(event->pos());
	if (pos.column == -1 || pos.row == -1)
		return;

	Step step;
	step.pos = pos;
	step.qizi = m_gameCtrl->myQizi();
	emit dropMine(step);
    
    QWidget::mousePressEvent(event);
}

Pos Panel::pointToPos(const QPoint& pt)
{
	float gridWidth = 1.0f * m_validRect.width() / (m_column-1);
	float gridHeight = 1.0f * m_validRect.height() / (m_row-1);
	float offsetX = gridWidth / 3.0f;
	float offsetY = gridHeight / 3.0f;

	Pos pos;
	pos.column = pos.row = -1;

	if (pt.x() < (m_validRect.left() - offsetX) ||
		pt.x() > (m_validRect.left() + m_validRect.width() + offsetX) ||
		pt.y() < (m_validRect.top() - offsetY) ||
		pt.y() > (m_validRect.top() + m_validRect.height() + offsetY))
	{
		return pos;
	}

	for (int c = 0; c < m_column; c++)
	{
		float x = m_validRect.left() + c * gridWidth;
		if (pt.x() >= (x - offsetX) &&
			pt.x() <= (x + offsetX))
		{
			pos.column = c;
			break;
		}
	}

	for (int r = 0; r < m_row; r++)
	{
		float y = m_validRect.top() + r * gridHeight;
		if (pt.y() >= (y - offsetY) &&
			pt.y() <= (y + offsetY))
		{
			pos.row = r;
			break;
		}
	}

	return pos;
}

QPoint Panel::posToPoint(const Pos& pos)
{
	float gridWidth = 1.0f * m_validRect.width() / (m_column - 1);
	float gridHeight = 1.0f * m_validRect.height() / (m_row - 1);

	QPoint pt;
	pt.setX(m_validRect.left() + pos.column * gridWidth);
	pt.setY(m_validRect.top() + pos.row * gridHeight);

	return pt;
}

void Panel::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    static QPixmap board(":/res/board.png");
    painter.drawPixmap(rect(), board);
    
    QWidget::paintEvent(event);
}

void Panel::dropQizi(Step step)
{
	m_gameCtrl->drop(step);
	QiziWidget* widget = new QiziWidget(this, step.qizi);
	widget->resize(28, 28);
	QPoint pt = posToPoint(step.pos);
	widget->move(pt.x() - widget->width() / 2,
				 pt.y() - widget->height() / 2);
	widget->show();

	StepRecord record;
	record.step = step;
	record.qiziWidget = widget;
	m_stepRecord.push(record);

	if (m_gameCtrl->checkWin(step))
		emit win(step.qizi);
}

void Panel::regret(Qizi qizi)
{
	while (!m_stepRecord.empty())
	{
		StepRecord last = m_stepRecord.top();
		
		delete last.qiziWidget;
		m_gameCtrl->remove(last.step.pos);
		m_stepRecord.pop();

		if (last.step.qizi == qizi)
			break;
	}

	if (qizi == m_gameCtrl->myQizi())
		m_gameCtrl->setMyTurn(true);
	else
		m_gameCtrl->setMyTurn(false);
}