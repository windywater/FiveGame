#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include "Common.h"
#include "Network.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

	void reset();
	void showInfo(const QString& text);
    
protected slots:
    //void onHost();
    void onRegret();
	void onConnectClicked();

	//void onReceiveHost(QHostAddress addr);
	void onOtherConnected();
	void onJoinGame(Qizi qizi, bool firstDrop);
	void onDropMine(Step step);
	void onWin(Qizi qizi);
	void onQiziDropped(Step step);
	void onOtherAsksRegret();
	void onOtherRespondsRegret(bool agree);

private:
    Ui::MainWindow *ui;
    Network* m_network;
	bool m_regretAsked;
};

#endif // MAINWINDOW_H
