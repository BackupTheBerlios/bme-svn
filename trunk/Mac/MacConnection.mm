/*
 *  MacConnection.cpp
 *  Bme
 *
 *  Created by Tim De Jong on 17-05-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */

#import "MacConnection.h"

MacConnection::MacConnection(std::string url, unsigned short port, IConnection::ConnectionType connectionType, SecurityLevel securityLevel)
				:	m_url(url),
					m_connectionType(connectionType)
{
	//convert the url string into an Objective C NSString
	NSString* urlString = [[NSString alloc] initWithCString:m_url.c_str()];
	//get input and output streams for the url, we can read from and write to	
	NSInteger p = port;
	
	m_connection = [[Connection alloc] initWithURL:urlString andPort:p andSecurity:securityLevel withOwner:this];	
	
	NSLock* lock = [[NSLock alloc] init];
	this->m_connectionLock = [lock retain];
	[lock release];
	
}

MacConnection::~MacConnection()
{
	NSLog(@"in MacConnection");
	//delete connection listeners
	for (CI c = m_connectionListeners.begin(); c != m_connectionListeners.end(); ++c)
	{
		IConnectionListener* connectionListener = (IConnectionListener*)*c;
		delete connectionListener;
	}

	[m_connection release];
	
	while (!this->Lock());
	this->Unlock();
	[this->m_connectionLock release];
	
}

void MacConnection::Close()
{
	NSLog(@"Close");
	
	while (!this->Lock());
	NSLog(@"Close has lock");
	
	[m_connection close];
	this->Unlock();
	NSLog(@"Close unlocked");
}

bool MacConnection::IsConnected()
{	
	return [m_connection isConnected] ? true : false;
}

std::string	MacConnection::URL()	
{
	return m_url;
}

size_t MacConnection::WriteBytes(const uint8_t *bytes, uint32_t length)
{
	[m_connection writeBytes:bytes maxLength:length];
	return length;
}

bool MacConnection::Lock()
{
	return [m_connectionLock tryLock] ? true : false;
}

void MacConnection::Unlock()
{
	[m_connectionLock unlock];
}

void MacConnection::AddConnectionListener(IConnectionListener* connectionListener)
{
	m_connectionListeners.push_back(connectionListener);
}

void MacConnection::DidConnect()
{
	for (CI c = m_connectionListeners.begin(); c != m_connectionListeners.end(); ++c)
	{
		IConnectionListener* connectionListener = (IConnectionListener*)*c;
		connectionListener->DidConnect();
	}
}

void MacConnection::BytesSent(size_t length)
{
	for (CI c = m_connectionListeners.begin(); c != m_connectionListeners.end(); ++c)
	{
		IConnectionListener* connectionListener = (IConnectionListener*)*c;
		connectionListener->BytesSent(this, length);
	}
}

void MacConnection::BytesRead(uint8_t* bytes, size_t length)
{
	for (CI c = m_connectionListeners.begin(); c != m_connectionListeners.end(); ++c)
	{
		IConnectionListener* connectionListener = (IConnectionListener*)*c;
		connectionListener->BytesRead(this, bytes, length);
	}
}

@implementation Connection

@synthesize socket;

-(id)initWithURL:(NSString*)url andPort:(NSInteger)port andSecurity:(IConnection::SecurityLevel)securityLevel withOwner:(MacConnection*)macConnection
{
	self = [super init];
	if (self)
	{
		m_macConnection = macConnection;
				
		NSString* socketSecurity = nil;
		switch (securityLevel)
		{
			case IConnection::K_NO_SECURITY:
			{
				socketSecurity = NSStreamSocketSecurityLevelNone;
			}
			break;
			case IConnection::K_SSL_V2_SECURITY:
			{
				socketSecurity = NSStreamSocketSecurityLevelSSLv2;
				
			}
			break;
			default:
			{
				socketSecurity = NSStreamSocketSecurityLevelNone;
			}
			break;
		}
			
		AsyncSocket* s = [[AsyncSocket alloc] initWithDelegate:self];
		self.socket = s;
		[s release];
		
		[socket connectToHost:url onPort:port error:nil];
		
		
		NSDictionary *settings = nil;
		if (securityLevel != IConnection::K_NO_SECURITY)
		{						
			settings = [[NSDictionary alloc] initWithObjectsAndKeys:
						[NSNumber numberWithBool:NO], kCFStreamSSLAllowsExpiredCertificates,
						[NSNumber numberWithBool:NO], kCFStreamSSLAllowsAnyRoot,
						[NSNumber numberWithBool:NO], kCFStreamSSLValidatesCertificateChain,
						url,kCFStreamSSLPeerName,
						socketSecurity,kCFStreamSSLLevel,
						nil];		
			[self.socket startTLS:settings];
		}
	}

	return self;
}

-(void)dealloc
{
	[socket release];
	[super dealloc];
}

-(void)writeBytes:(const uint8_t*)bytes maxLength:(NSUInteger)length
{
	//write the data to the socket with no timeout
	NSData* data = [NSData dataWithBytes:bytes length:length];
	[self.socket writeData:data withTimeout:-1 tag:0];
	//start reading for received data at the same time
	[self.socket readDataWithTimeout:-1 tag:0];
}

-(BOOL)isConnected
{	
	BOOL connected = [self.socket isConnected];
	return connected;
}

-(void)close
{
	[self.socket disconnect];
}

-(void)onSocket:(AsyncSocket *)sock didReadData:(NSData *)data withTag:(long)tag
{
	size_t length = [data length];
	uint8 bytes[length];
	//copy read bytes into a buffer
	[data getBytes:&bytes length:length];
	//inform our listeners bytes have been read
	m_macConnection->BytesRead(bytes, length);
}

-(void)onSocket:(AsyncSocket *)sock didWriteDataWithTag:(long)tag
{
	//m_macConnection->BytesSent(length);
}

-(void)onSocket:(AsyncSocket *)sock didConnectToHost:(NSString *)host port:(UInt16)port
{
	m_macConnection->DidConnect();
}

-(void)onSocketDidDisconnect:(AsyncSocket *)sock 
{
	NSLog(@"Socket disconnected");
}

@end

