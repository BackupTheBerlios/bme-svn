/*
 *  MacConnection.h
 *  Bme
 *
 *  Created by Tim De Jong on 17-05-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef MAC_CONNECTION_H
#define MAC_CONNECTION_H

#include <string>
#include <vector>
#import <Foundation/Foundation.h>
#import "AsyncSocket.h"
#include "IConnection.h"
#include "IConnectionListener.h"

class MacConnection;

@interface Connection : NSObject<AsyncSocketDelegate>
{	
	AsyncSocket* socket;
	NSTimer* readTimer;
	BOOL readingData;
	
	MacConnection* m_macConnection;	
}

@property (nonatomic, retain) AsyncSocket* socket;
@property (nonatomic, retain) NSTimer* readTimer;
@property BOOL readingData;

-(id)initWithURL:(NSString*)url andPort:(NSInteger)port andSecurity:(IConnection::SecurityLevel)securityLevel withOwner:(MacConnection*)macConnection;
-(void)writeBytes:(const uint8_t*)bytes maxLength:(NSUInteger)length;
-(void)readBytes;
-(void)readFromServerInTimer;
-(BOOL)isConnected;
-(void)close;

-(void)onSocket:(AsyncSocket *)sock didReadData:(NSData *)data withTag:(long)tag;
-(void)onSocket:(AsyncSocket *)sock didConnectToHost:(NSString *)host port:(UInt16)port;
-(void)onSocketDidDisconnect:(AsyncSocket *)sock;
@end

class MacConnection : public IConnection
{
public:
	MacConnection(std::string url, unsigned short port, IConnection::ConnectionType connectionType, SecurityLevel securityLevel = K_NO_SECURITY);
	virtual ~MacConnection();
	
	virtual void Close();
	virtual bool IsConnected();
	virtual std::string	URL();	
	
	virtual size_t WriteBytes(const uint8_t *bytes, uint32_t length);
	virtual void ReadBytes();
	
	virtual void AddConnectionListener(IConnectionListener* connectionListener);
	virtual void DidConnect();
	virtual void DidDisconnect();
	virtual void BytesSent(size_t length);
	virtual void BytesRead(uint8_t* bytes, size_t length);
		
private:
	std::string m_url;
	Connection* m_connection;
	
	typedef std::vector<IConnectionListener*>::iterator CI;
	std::vector<IConnectionListener*> m_connectionListeners;

	IConnection::ConnectionType m_connectionType;
		
};

#endif