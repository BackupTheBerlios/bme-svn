/*
 *  ServerConnection.h
 *  Bme
 *
 *  Created by Tim De Jong on 04-05-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#include <vector>
#include <queue>
#include "ProtocolConstants.h"
#include "IThread.h"
#include "IRunnable.h"
#include "IConnection.h"
#include "IConnectionManager.h"
#include "ProtocolMessage.h"
#include "IConnectionListener.h"

class ProtocolHandler;

using namespace std;

class ServerConnection : public IThreadListener, public IConnectionListener
{
public:
	ServerConnection(IConnectionManager* connectionManager);
	virtual ~ServerConnection();
	
	virtual IConnection* GetConnection();
	virtual void Connect(std::string address, int32_t port); 
	virtual void Close();
	
	virtual void SendCommandMessage(ProtocolMessage* message);
	virtual void CommandMessageReceived(ProtocolMessage* message); //ServerReceivingThread delegate?
	
	virtual void AddMessageHandler(ProtocolHandler* handler);
	virtual bool RemoveMessageHandler(ProtocolHandler* handler);
	
	virtual void ThreadStopped(IThread* thread);
		
	virtual void BytesSent(IConnection* connection, size_t length);
	virtual void BytesRead(IConnection* connection, uint8_t* bytes, size_t length);
	
private:
	IConnectionManager*				m_connectionManager;
	IConnection*					m_connection;
	IThread*						m_receiverThread;
	vector<ProtocolHandler*>		m_protocolHandlers;
	
	queue<ProtocolMessage*> m_messageQueue;
	std::string				m_messageCacheString;
};

class ServerReceiverRunnable : public IRunnable
{
public:
	ServerReceiverRunnable(ServerConnection* serverConnection);
	virtual ~ServerReceiverRunnable();
	
	virtual bool Run();
	
private:	
	ServerConnection*		m_serverConnection;
	IConnection*			m_readConnection;
	queue<ProtocolMessage*> m_messageQueue;
	std::string				m_messageCacheString;
};

#endif
