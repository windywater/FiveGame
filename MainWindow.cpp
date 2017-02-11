#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	ui->m_gamePanel->create(QRect(19, 19, 412, 412), 15, 15);

    //connect(ui->m_hostButton, SIGNAL(clicked()), this, SLOT(onHost()));
    connect(ui->m_regretButton, SIGNAL(clicked()), this, SLOT(onRegret()));
	connect(ui->m_connectButton, SIGNAL(clicked()), this, SLOT(onConnectClicked()));
    
    m_network = new Network(this);
	//connect(m_network, SIGNAL(receiveHost(QHostAddress)), this, SLOT(onReceiveHost(QHostAddress)));
	connect(m_network, SIGNAL(otherConnected()), this, SLOT(onOtherConnected()));
	connect(m_network, SIGNAL(joinGame(Qizi, bool)), this, SLOT(onJoinGame(Qizi, bool)));
	connect(ui->m_gamePanel, SIGNAL(dropMine(Step)), this, SLOT(onDropMine(Step)));
	connect(ui->m_gamePanel, SIGNAL(win(Qizi)), this, SLOT(onWin(Qizi)));
	connect(m_network, SIGNAL(otherDrops(Step)), this, SLOT(onQiziDropped(Step)));
	connect(m_network, SIGNAL(otherAsksRegret()), this, SLOT(onOtherAsksRegret()));
	connect(m_network, SIGNAL(otherRespondsRegret(bool)), this, SLOT(onOtherRespondsRegret(bool)));

	QList<QHostAddress> localAddresses = m_network->localAddresses();
	foreach(const QHostAddress& addr, localAddresses)
	{
		ui->m_localAddrCombo->addItem(addr.toString());
	}

	reset();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reset()
{
	ui->m_gamePanel->reset();
	m_network->close();
	m_regretAsked = false;

	showInfo(tr("Game ready."));
}

//void MainWindow::onHost()
//{
//    m_network->broadcastToHost();
//	showInfo(tr("Host message has been sent."));
//}

void MainWindow::onRegret()
{
	// already regret
	if (m_regretAsked)
		return;

	m_network->askRegret();
	m_regretAsked = true;
	showInfo(tr("Ask to regret..."));
}

void MainWindow::onConnectClicked()
{
	m_network->join(ui->m_serverAddr->text());
}

//void MainWindow::onReceiveHost(QHostAddress addr)
//{
//	QString text = tr("Received host from %1, join it?").arg(addr.toString());
//	if (QMessageBox::question(this, tr("Query"), text, QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes)
//		m_network->join(addr);
//}

void MainWindow::onOtherConnected()
{
	ui->m_gamePanel->start(BLACK_QIZI, true);
	m_network->notifyStart(WHITE_QIZI, false);

	showInfo(tr("A player has joined. You go first."));
}

void MainWindow::onJoinGame(Qizi qizi, bool firstDrop)
{
	ui->m_gamePanel->start(qizi, firstDrop);

	showInfo(tr("Joined, wait for the other player."));
}

void MainWindow::onDropMine(Step step)
{
	m_network->notifyDrop(step);
	onQiziDropped(step);
}

void MainWindow::onWin(Qizi qizi)
{
	if (qizi == ui->m_gamePanel->myQizi())
	{
		QMessageBox::information(this, tr("Win"), tr("You win the game!"));
	}
	else
	{
		QMessageBox::information(this, tr("Lose"), tr("You lose the game!"));
	}

	reset();
}

void MainWindow::onQiziDropped(Step step)
{
	if (step.qizi == ui->m_gamePanel->myQizi())
		showInfo(tr("Wait for the other player."));
	else
		showInfo(tr("It's my turn to play."));

	ui->m_gamePanel->dropQizi(step);
}

void MainWindow::onOtherAsksRegret()
{
	if (QMessageBox::question(this, tr("Regret"), tr("The other play asks to regret, agree?"),
		QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
	{
		m_network->respondRegret(true);
		ui->m_gamePanel->regret(ui->m_gamePanel->otherQizi());
	}
	else
	{
		m_network->respondRegret(false);
	}
}

void MainWindow::onOtherRespondsRegret(bool agree)
{
	if (agree)
	{
		ui->m_gamePanel->regret(ui->m_gamePanel->myQizi());
	}
	else
	{
		QMessageBox::information(this, tr("Regret"), tr("The other player disagrees to regret."));
	}
	
	m_regretAsked = false;
}

void MainWindow::showInfo(const QString& text)
{
	ui->m_info->setText(text);
}