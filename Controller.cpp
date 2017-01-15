#include "Controller.h"

Controller::Controller(QObject *parent, int row, int column) 
    : QObject(parent),
      m_row(row),
      m_column(column)
{
    m_board = new Qizi*[m_row];
    for (int r = 0; r < m_row; r++)
        m_board[r] = new Qizi[m_column];
}

Controller::~Controller()
{
	for (int r = 0; r < m_row; r++)
		delete[] m_board[r];

	delete[] m_board;
}

void Controller::reset()
{
	m_myQizi = BLACK_QIZI;
	m_myTurn = false;
	clear();
}

void Controller::start(Qizi qizi, bool firstDrop)
{
	m_myQizi = qizi;
	m_myTurn = firstDrop;
	clear();
}

bool Controller::drop(Step step)
{
	if (m_board[step.pos.column][step.pos.row] != EMPTY_QIZI)
		return false;

	m_board[step.pos.column][step.pos.row] = step.qizi;

	if (step.qizi == m_myQizi)
		m_myTurn = false;
	else
		m_myTurn = true;

    return true;
}

bool Controller::remove(Pos pos)
{
	if (m_board[pos.column][pos.row] == EMPTY_QIZI)
		return false;

	m_board[pos.column][pos.row] = EMPTY_QIZI;
    return true;
}

void Controller::clear()
{
	for (int c = 0; c < m_column; c++)
		for (int r = 0; r < m_row; r++)
			m_board[c][r] = EMPTY_QIZI;
}

Qizi Controller::myQizi()
{
	return m_myQizi;
}

Qizi Controller::otherQizi()
{
	if (m_myQizi == BLACK_QIZI)
		return WHITE_QIZI;
	else if (m_myQizi == WHITE_QIZI)
		return BLACK_QIZI;

	return EMPTY_QIZI;
}

bool Controller::isMyTurn()
{
	return m_myTurn;
}

void Controller::setMyTurn(bool myTurn)
{
	m_myTurn = myTurn;
}

Qizi Controller::getQizi(Pos pos)
{
	return m_board[pos.column][pos.row];
}

bool Controller::checkWin(Step lastStep)
{
	int up = countSameQizi(lastStep, 0, -1);
	int down = countSameQizi(lastStep, 0, 1);
	if (up + down >= 4)
		return true;

	int left = countSameQizi(lastStep, -1, 0);
	int right = countSameQizi(lastStep, 1, 0);
	if (left + right >= 4)
		return true;

	int leftUp = countSameQizi(lastStep, -1, -1);
	int rightDown = countSameQizi(lastStep, 1, 1);
	if (leftUp + rightDown >= 4)
		return true;

	int upRight = countSameQizi(lastStep, 1, -1);
	int downLeft = countSameQizi(lastStep, -1, 1);
	if (upRight + downLeft >= 4)
		return true;

    return false;
}

int Controller::countSameQizi(Step step, int colOffset, int rowOffset)
{
	Pos besidePos;
	besidePos.column = step.pos.column + colOffset;
	besidePos.row = step.pos.row + rowOffset;

	if (besidePos.column < 0 ||
		besidePos.row >= m_column ||
		besidePos.row < 0 ||
		besidePos.row >= m_row)
		return 0;

	if (getQizi(besidePos) == step.qizi)
	{
		Step besideStep;
		besideStep.pos = besidePos;
		besideStep.qizi = step.qizi;
		return countSameQizi(besideStep, colOffset, rowOffset) + 1;
	}

	return 0;
}
