/*
 *  ServerConnection.cpp
 *  Bme
 *
 *  Created by Tim De Jong on 04-05-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */

#include "ServerConnection.h"
#include "PlatformSpecific.h"
#include "ProtocolHandler.h"
#include <iostream>

ServerConnection::ServerConnection(IConnectionManager* connectionManager)
					:	IThreadListener(),
						IConnectionListener(),
						m_connectionManager(connectionManager),
						m_connection(NULL)
{
}

ServerConnection::~ServerConnection()
{
	//close the server connection
//	this->Close();	//TODO: what if close is called twice???
	//clean up all handlers here
	typedef vector<ProtocolHandler*>::const_iterator PI;
	for (PI p = m_protocolHandlers.begin(); p != m_protocolHandlers.end();++p)
	{
		ProtocolHandler* handler = *p;
		delete handler;
	}
	delete m_connection;
}

void ServerConnection::Connect(std::string address, int32_t port)
{	
	m_connection = m_connectionManager->OpenConnection(address, port, IConnection::K_READ_WRITE);
	m_connection->AddConnectionListener(this);
	//setup receiver thread
/*	ServerReceiverRunnable* receiverRunnable = new ServerReceiverRunnable(this);
	m_receiverThread = PlatformSpecific::GetThread(receiverRunnable);
	m_receiverThread->SetThreadListener(this);
	m_receiverThread->Start();*/
}

void ServerConnection::Close()
{	
	//stop receiver thread
//	m_receiverThread->Stop();
	//delete the server connection after closing the receiver thread
	//m_connection->Close();		
}

IConnection* ServerConnection::GetConnection()
{
	return m_connection;
}

void ServerConnection::SendCommandMessage(ProtocolMessage* message)
{
	std::string messageString = message->ToString();	
		
	const char* cString = messageString.c_str();
	uint8_t* msg = (uint8_t*)cString;
	
//	while (!m_serverConnection->Lock());
	
	size_t totalWritten = 0;
	do 
	{
		size_t bytesWritten = m_connection->WriteBytes(&msg[totalWritten],strlen(cString) - totalWritten); //messageString.length() - totalWritten);
		totalWritten += bytesWritten;
	}
	while (totalWritten < strlen(cString)); //messageString.length());
	
//	m_serverConnection->Unlock();
	
	cout << "Message sent: " << messageString << " length = " << messageString.size() << " sent= " << totalWritten << endl;
	//if message has been sent delete it
	delete message;
}

void ServerConnection::CommandMessageReceived(ProtocolMessage* message)
{
	cout << "Message Received" << message->ToString() << endl;
	
	//loop through all handlers here and see if they can handled the received message
	typedef vector<ProtocolHandler*>::const_iterator PI;
	for (PI p = m_protocolHandlers.begin(); p != m_protocolHandlers.end();++p)
	{
		ProtocolHandler* handler = *p;
		//see if this handler handles the current protocol message
		if (handler->IsHandlerForMessage(message))
		{
			//handle the incoming protocol message with the selected handler
			handler->HandleMessage(message);			
			break;
		}
	}
}

void ServerConnection::AddMessageHandler(ProtocolHandler* handler)
{
	handler->SetServerConnection(this);
	m_protocolHandlers.push_back(handler);
}

bool ServerConnection::RemoveMessageHandler(ProtocolHandler* handler)
{
	//TODO: implement!
	return false;
}

void ServerConnection::AddServerConnectionListener(IServerConnectionListener* listener)
{
	m_serverConnectionListeners.push_back(listener);
}

void ServerConnection::ThreadStopped(IThread* thread)
{
	delete thread;
	//m_connection->Close();
}

void ServerConnection::DidConnect(IConnection* connection)
{	
	//loop through all handlers here and see if they can handled the received message
	typedef vector<IServerConnectionListener*>::const_iterator SI;
	for (SI p = m_serverConnectionListeners.begin(); p != m_serverConnectionListeners.end();++p)
	{
		IServerConnectionListener* listener = *p;
		listener->DidConnect();
	}
}

void ServerConnection::DidDisconnect(IConnection* connection)
{
	cout << "ServerConnection: DidDisconnect" << endl;
}

void ServerConnection::BytesSent(IConnection* connection, size_t length)
{
	cout << "BytesSent, length=" << length << endl;
}

void ServerConnection::BytesRead(IConnection* connection, uint8_t* bytes, size_t length)
{
	cout << "BytesRead, length=" << length << endl;
	
	if (length > 0)
	{
		//append the read bytes to our string cache
		m_messageCacheString.append((char*)bytes, length);
	}
	
	//if (m_messageCacheString.size() > 0)
	do
	{
		//check if there's already a message in the cache
		std::string delimiter = "\r\n";
		size_t delimiterPosition = m_messageCacheString.find(delimiter);
		//if message has been found 
		if (delimiterPosition != std::string::npos)
		{
			std::string messageString = m_messageCacheString.substr(0,delimiterPosition);
			//enough bytes have been read turn it into a message
			ProtocolMessage* message = ProtocolMessage::ProtocolMessageFromString(messageString);
			
			size_t messageEndPosition = delimiterPosition + delimiter.length();
			//check if we have a payload message or a normal message, create array of payload commands
			if (message->IsPayloadMessage())
			{					
				//payload message found, check if we have read enough bytes to complete the payload message
				uint32_t payloadSize = message->PayloadSize();
				size_t alreadyRead = m_messageCacheString.size();
				//if more bytes are already read than the size of the payload, the readLength should be < 0
				int32_t readLength = payloadSize - (alreadyRead - messageString.size());
				if (readLength > 0)
				{
					//not enough of the payload has been read yet, leave the message in the cache 
					//and parse it the next time data has been read
					break;
				}					
				std::string payload = m_messageCacheString.substr(messageEndPosition,payloadSize); 					
				message->SetPayloadString(payload);
				m_messageCacheString.erase(messageEndPosition, payloadSize);
			}			
			//remove message string from cache
			m_messageCacheString = m_messageCacheString.erase(0, messageEndPosition);
			//add message to the message queue
			m_messageQueue.push(message);					
		}
	}
	while (m_messageCacheString.size() > 0);
	
	//	connection->Unlock();
	
	//Handle the next message in the queue
	//if (!m_messageQueue.empty())
	
	do
	{
		ProtocolMessage* message = m_messageQueue.front();
		//handle message
		this->CommandMessageReceived(message);
		//remove handled message from the queue
		m_messageQueue.pop();
		//clean up message
		delete message;
	}
	while (!m_messageQueue.empty());
}

//=========ServerReceiverRunnable==========
ServerReceiverRunnable::ServerReceiverRunnable(ServerConnection* serverConnection)
						:	IRunnable(),
							m_serverConnection(serverConnection)
{
	m_readConnection = m_serverConnection->GetConnection();
}

ServerReceiverRunnable::~ServerReceiverRunnable()
{	
	//close the connection to the server
	m_readConnection->Close();
	delete m_readConnection;
	//clean up any messages left in the queue
	while(!m_messageQueue.empty())
	{
		//get the message still left in the queue
		ProtocolMessage* message = m_messageQueue.front();
		//remove the message from the queue
		m_messageQueue.pop();
		//delete the message
		delete message;		
	}	
}

bool ServerReceiverRunnable::Run()
{	
//	while (!connection->Lock());
	//read bytes from the socket and store them in a byte buffer
/*	uint8_t readBuffer[1024];
	size_t sizeRead = m_readConnection->ReadBytes(readBuffer,sizeof(readBuffer)/sizeof(uint8_t));
	if (sizeRead > 0)
	{
		//append the read bytes to our string cache
		m_messageCacheString.append((char*)readBuffer, sizeRead);
	}
	
	if (m_messageCacheString.size() > 0)
	{
		//check if there's already a message in the cache
		std::string delimiter = "\r\n";
		size_t delimiterPosition = m_messageCacheString.find(delimiter);
		//if message has been found 
		if (delimiterPosition != std::string::npos)
		{
			std::string messageString = m_messageCacheString.substr(0,delimiterPosition);
			//enough bytes have been read turn it into a message
			ProtocolMessage* message = ProtocolMessage::ProtocolMessageFromString(messageString);
			//remove message string from cache
			m_messageCacheString = m_messageCacheString.erase(0, delimiterPosition + delimiter.length());//TODO: check if this erases enough! 
			//check if we have a payload message or a normal message, create array of payload commands
			if (message->IsPayloadMessage())
			{					
				//payload message found, check if we have read enough bytes to complete the payload message
				uint32_t payloadSize = message->PayloadSize();
				size_t alreadyRead = m_messageCacheString.size();
				//if more bytes are already read than the size of the payload, the readLength should be < 0
				int32_t readLength = payloadSize - alreadyRead;
				if (readLength > 0)
				{
					uint8_t additionalBuffer[readLength];
					//if not, read additional bytes
					size_t readAdditional = m_readConnection->ReadBytes(additionalBuffer, sizeof(additionalBuffer)/sizeof(uint8_t));
					m_messageCacheString.append((char*)additionalBuffer, readAdditional);
				}
				std::string payload = m_messageCacheString.substr(0,payloadSize); 					
				message->SetPayloadString(payload);
				m_messageCacheString.erase(0, payloadSize);
			}				
			//add message to the message queue
			m_messageQueue.push(message);					
		}
	}
	
//	connection->Unlock();
	
	//Handle the next message in the queue
	if (!m_messageQueue.empty())
	{
		ProtocolMessage* message = m_messageQueue.front();
		//handle message
		m_serverConnection->CommandMessageReceived(message);
		//remove handled message from the queue
		m_messageQueue.pop();
		//clean up message
		delete message;
	}*/
	
	return m_readConnection->IsConnected();
}
