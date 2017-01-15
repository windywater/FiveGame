#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "Common.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent, int row, int column);
    ~Controller();
    
	void reset();
	void start(Qizi qizi, bool firstDrop);
    bool drop(Step step);
    bool remove(Pos pos);
    void clear();
	Qizi myQizi();
	Qizi otherQizi();
	bool isMyTurn();
	void setMyTurn(bool myTurn);
	bool checkWin(Step lastStep);

signals:
    void gameOver(Qizi qizi);

protected:
	Qizi getQizi(Pos pos);
	int countSameQizi(Step step, int colOffset, int rowOffset);
    
protected:
    int m_row;
    int m_column;
    Qizi** m_board;
	Qizi m_myQizi;
	bool m_myTurn;
};

#endif // CONTROLLER_H
