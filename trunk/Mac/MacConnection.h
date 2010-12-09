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
#include "IConnection.h"
#include "IConnectionListener.h"
#include "ISSLConnection.h"

class MacConnection;

@interface Connection : NSObject<NSStreamDelegate>
{
	NSMutableString* incomingData;
	NSMutableString* outgoingData;
	
	NSInputStream* inputStream;
	NSOutputStream* outputStream;
	MacConnection* m_macConnection;
	BOOL m_didNotWriteToOutputStream;
}

@property (nonatomic, retain) NSMutableString* incomingData;
@property (nonatomic, retain) NSMutableString* outgoingData;
@property (nonatomic, retain) NSInputStream* inputStream;
@property (nonatomic, retain) NSOutputStream* outputStream;

-(id)initWithURL:(NSString*)url andPort:(NSInteger)port andSecurity:(IConnection::SecurityLevel)securityLevel withOwner:(MacConnection*)macConnection;
-(void)writeBytes:(const uint8_t*)bytes maxLength:(NSUInteger)length;
-(size_t)readBytes:(uint8_t*) buffer maxLength:(NSUInteger)length;
-(BOOL)isConnected;
-(void)close;
-(void)stream:(NSStream *)theStream handleEvent:(NSStreamEvent)streamEvent;

@end

class MacConnection : public ISSLConnection
{
public:
	MacConnection(std::string url, unsigned short port, IConnection::ConnectionType connectionType, SecurityLevel securityLevel = K_NO_SECURITY);
	virtual ~MacConnection();
	
	virtual void Close();
	virtual bool IsConnected();
	virtual std::string	URL();	
	
	virtual size_t WriteBytes(const uint8_t *bytes, uint32_t length);
	virtual size_t ReadBytes(uint8_t *bytes, uint32_t length);
	
	virtual bool Lock();
	virtual void Unlock();
	
	virtual void AddConnectionListener(IConnectionListener* connectionListener);
	virtual void BytesSent(size_t length);
	virtual void BytesRead(uint8_t* bytes, size_t length);
		
private:
	std::string m_url;
	Connection* m_connection;
	
	typedef std::vector<IConnectionListener*>::iterator CI;
	std::vector<IConnectionListener*> m_connectionListeners;
	
	/*NSInputStream* m_inputStream;
	NSOutputStream* m_outputStream;*/
	NSLock* m_connectionLock;
	IConnection::ConnectionType m_connectionType;
		
};

#endif