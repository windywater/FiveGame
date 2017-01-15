#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QUdpSocket>
#include "Common.h"

class Network : public QObject
{
    Q_OBJECT
public:
    explicit Network(QObject *parent = 0);
    ~Network();

    void broadcastToHost();
    void join(QHostAddress addr);
    void askRegret();
	void respondRegret(bool agree);
    void notifyStart(Qizi otherQizi, bool firstDrop);
    void notifyDrop(Step step);

	void close();
protected:
    void init();

signals:
	void receiveHost(QHostAddress addr);
	void otherConnected();
	void joinGame(Qizi qizi, bool firstDrop);
	void otherDrops(Step step);
	void otherAsksRegret();
	void otherRespondsRegret(bool agree);

protected slots:
    void onClientArrives();
    void onTcpRead();
    void onUdpRead();

protected:
	QHostAddress m_myAddress;
	quint16 m_tcpPort;
	quint16 m_udpPort;
    QTcpServer* m_tcpServer;
    QTcpSocket* m_clientSocket;
    QTcpSocket* m_mySocket;
    QUdpSocket* m_udpSocket;
    bool m_isHost;

};

#endif // NETWORK_H
