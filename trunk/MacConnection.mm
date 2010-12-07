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
/*	NSHost* host = [NSHost hostWithName:urlString];
	[urlString release];	
	
	
	
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
	
	NSDictionary *settings = nil;
	if (securityLevel != IConnection::K_NO_SECURITY)
	{
		settings = [[NSDictionary alloc] initWithObjectsAndKeys:
								  [NSNumber numberWithBool:YES], kCFStreamSSLAllowsExpiredCertificates,
								  [NSNumber numberWithBool:YES], kCFStreamSSLAllowsAnyRoot,
								  [NSNumber numberWithBool:NO], kCFStreamSSLValidatesCertificateChain,
								  kCFNull,kCFStreamSSLPeerName,
								  nil];		
	}
	
	switch (connectionType)
	{
		case K_READ_ONLY:
		{
			[NSStream getStreamsToHost:host port:p  inputStream:&this->m_inputStream outputStream:nil];
			this->m_outputStream = nil;	
			[this->m_inputStream retain];
			[this->m_inputStream setProperty:socketSecurity forKey:NSStreamSocketSecurityLevelKey];
					
			if (settings)
			{
				CFReadStreamSetProperty((CFReadStreamRef)this->m_inputStream, kCFStreamPropertySSLSettings, (CFTypeRef)settings);
			}
			[this->m_inputStream open];
		}
		break;
		case K_WRITE_ONLY:
		{			
			[NSStream getStreamsToHost:host port:p  inputStream:nil outputStream:&this->m_outputStream];
			this->m_inputStream = nil;
			[this->m_outputStream retain];
			[this->m_outputStream setProperty:socketSecurity forKey:NSStreamSocketSecurityLevelKey];
			
			if (settings)
			{
				CFWriteStreamSetProperty((CFWriteStreamRef)this->m_outputStream, kCFStreamPropertySSLSettings, (CFTypeRef)settings);
			}
			[this->m_outputStream open];
		}
		break;			
		case K_READ_WRITE:
		{
			[NSStream getStreamsToHost:host port:p  inputStream:&this->m_inputStream outputStream:&this->m_outputStream];
			
			[this->m_inputStream retain];
			[this->m_outputStream retain];
			
			[this->m_inputStream setProperty:socketSecurity forKey:NSStreamSocketSecurityLevelKey];
			[this->m_outputStream setProperty:socketSecurity forKey:NSStreamSocketSecurityLevelKey];
			
			
			if (settings)
			{
				CFReadStreamSetProperty((CFReadStreamRef)this->m_inputStream, kCFStreamPropertySSLSettings, (CFTypeRef)settings);
				CFWriteStreamSetProperty((CFWriteStreamRef)this->m_outputStream, kCFStreamPropertySSLSettings, (CFTypeRef)settings);
			}
			[this->m_inputStream open];
			[this->m_outputStream open];
		}
		break;
		default:
		{
			[NSStream getStreamsToHost:host port:p  inputStream:&this->m_inputStream outputStream:&this->m_outputStream];
			
			[this->m_inputStream retain];
			[this->m_outputStream retain];
			
			[this->m_inputStream setProperty:socketSecurity forKey:NSStreamSocketSecurityLevelKey];
			[this->m_outputStream setProperty:socketSecurity forKey:NSStreamSocketSecurityLevelKey];
			
			if (settings)
			{
				CFReadStreamSetProperty((CFReadStreamRef)this->m_inputStream, kCFStreamPropertySSLSettings, (CFTypeRef)settings);
				CFWriteStreamSetProperty((CFWriteStreamRef)this->m_outputStream, kCFStreamPropertySSLSettings, (CFTypeRef)settings);
			}
			[this->m_inputStream open];
			[this->m_outputStream open];
		}
		break;
	}*/		
	
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
	
	
/*	[this->m_inputStream release];
	[this->m_outputStream release];*/
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
	/*[m_inputStream close];
	[m_outputStream close];*/
	[m_connection close];
	this->Unlock();
	NSLog(@"Close unlocked");
}

bool MacConnection::IsConnected()
{	
	
	/*switch (m_connectionType)
	{
		case K_READ_ONLY:
		{
			return ([m_inputStream streamStatus] != NSStreamStatusClosed);
		}
			break;
		case K_WRITE_ONLY:
		{
			return ([m_outputStream streamStatus] != NSStreamStatusClosed);
		}
		break;			
		case K_READ_WRITE:
		{
			return ([m_inputStream streamStatus] != NSStreamStatusClosed) && ([m_outputStream streamStatus] != NSStreamStatusClosed);
		}
		break;
		default:
		{
			return ([m_inputStream streamStatus] != NSStreamStatusClosed) && ([m_outputStream streamStatus] != NSStreamStatusClosed);
		}
		break;
	}	
	
	return false;*/
	return [m_connection isConnected] ? true : false;
}

std::string	MacConnection::URL()	
{
	return m_url;
}

//TODO: keep connection alive!
size_t MacConnection::WriteBytes(const uint8_t *bytes, uint32_t length)
{
	//while (!this->Lock());
	//NSLog(@"Write bytes has lock");
	
//	NSInteger bytesWritten = 0;
/*
//	if ([m_outputStream hasSpaceAvailable])
//	{
		
		NSError* error = [m_outputStream streamError];	
		NSLog(@"connection status %d and error: %@", [m_outputStream streamStatus], [error localizedDescription]);
		
		NSString* mString = [[NSString alloc] initWithBytes:bytes length:length encoding:NSASCIIStringEncoding];
		
		const char* rawString = [mString cStringUsingEncoding:NSUTF8StringEncoding];
		const uint8_t* rString = (const uint8_t*)rawString; 
		bytesWritten = [m_outputStream write:rString maxLength:[mString lengthOfBytesUsingEncoding:NSUTF8StringEncoding]];
		[mString release];
//	}
 */
	[m_connection writeBytes:bytes maxLength:length];
	//this->Unlock();
	//NSLog(@"Write bytes unlocked");
	//return (bytesWritten == -1) ? 0 : bytesWritten;
	return length;
}

size_t MacConnection::ReadBytes(uint8_t *bytes, uint32_t length)
{	
//	while (!this->Lock());
	//NSLog(@"Read bytes has lock");
	
	NSInteger bytesRead = 0;
/*
//	if ([m_inputStream hasBytesAvailable])
//	{
		NSError* error = [m_inputStream streamError];	
		NSLog(@"connection status %d and error: %@", [m_inputStream streamStatus], [error localizedDescription]);
		
		bytesRead = [m_inputStream read:bytes maxLength:(NSUInteger)length];
//	}
*/
	bytesRead = [m_connection readBytes:bytes maxLength:length];
///	this->Unlock();
	//NSLog(@"Read bytes unlocked");
		
	return (bytesRead == -1) ? 0 : bytesRead;
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

@synthesize inputStream, outputStream, incomingData, outgoingData;

-(id)initWithURL:(NSString*)url andPort:(NSInteger)port andSecurity:(IConnection::SecurityLevel)securityLevel withOwner:(MacConnection*)macConnection
{
	self = [super init];
	if (self)
	{
		m_macConnection = macConnection;
		
		NSMutableString* inDict = [[NSMutableString alloc] initWithCapacity:1024];
		self.incomingData = inDict;
		[inDict release];		
		
		NSMutableString* outDict = [[NSMutableString alloc] initWithCapacity:1024];
		self.outgoingData = outDict;
		[outDict release];
		
		NSHost* host = [NSHost hostWithName:url];
		
		[NSStream getStreamsToHost:host port:port inputStream:&inputStream outputStream:&outputStream];
		
		[inputStream retain];
		[outputStream retain];
		
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
		
		NSDictionary *settings = nil;
		if (securityLevel != IConnection::K_NO_SECURITY)
		{
			[inputStream setProperty:socketSecurity forKey:NSStreamSocketSecurityLevelKey];
			[outputStream setProperty:socketSecurity forKey:NSStreamSocketSecurityLevelKey];
						
			settings = [[NSDictionary alloc] initWithObjectsAndKeys:
						[NSNumber numberWithBool:YES], kCFStreamSSLAllowsExpiredCertificates,
						[NSNumber numberWithBool:YES], kCFStreamSSLAllowsAnyRoot,
						[NSNumber numberWithBool:NO], kCFStreamSSLValidatesCertificateChain,
						kCFNull,kCFStreamSSLPeerName,
						nil];		
									
			if (settings)
			{
				CFReadStreamSetProperty((CFReadStreamRef)inputStream, kCFStreamPropertySSLSettings, (CFTypeRef)settings);
				CFWriteStreamSetProperty((CFWriteStreamRef)outputStream, kCFStreamPropertySSLSettings, (CFTypeRef)settings);
			}	
			[settings release];
		}			
		
		[inputStream setDelegate:self];
		[outputStream setDelegate:self];
		
		[inputStream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
		[outputStream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
		
		[inputStream open];
		[outputStream open];		
	}

	return self;
}

-(void)dealloc
{
	[inputStream release];
	[outputStream release];
	[incomingData release];
	[outgoingData release];
	
	[super dealloc];
}

-(void)writeBytes:(const uint8_t*)bytes maxLength:(NSUInteger)length
{
	if (m_didNotWriteToOutputStream)
	{
		[outputStream write:bytes maxLength:length];
	}
	else 
	{
		NSString* data = [[NSString alloc] initWithBytes:bytes length:length encoding:NSASCIIStringEncoding];
		[outgoingData appendString:data];
		[data release];
	}
}

-(size_t)readBytes:(uint8_t*)buffer maxLength:(NSUInteger)length
{
	//[incomingData getBytes:buffer length:length]; //TODO: implement removing the bytes read from the code
	//return ([incomingData length] > length) ? length : [incomingData length];
	size_t returnLength = ([incomingData length] > length) ? length : [incomingData length];
	
	if (returnLength > 0)
	{
		NSRange range;
		range.location = 0;
		range.length = returnLength;
		//get the bytes to be returned
		[incomingData getBytes:buffer maxLength:length usedLength:NULL encoding:NSASCIIStringEncoding options:NSStringEncodingConversionAllowLossy range:range remainingRange:NULL];
		//erase the returned data from the incoming data buffer
		[incomingData deleteCharactersInRange:range];
	}
	
	return returnLength;
}

-(BOOL)isConnected
{	
	return ([inputStream streamStatus] != NSStreamStatusClosed) && ([outputStream streamStatus] != NSStreamStatusClosed);
}

-(void)close
{
	[inputStream close];
	[outputStream close];
}

-(void)stream:(NSStream *)stream handleEvent:(NSStreamEvent)streamEvent
{
//	NSLog(@"StreamEvent %d", streamEvent);
	
	switch (streamEvent) 
	{
		case NSStreamEventHasSpaceAvailable:
		{
			if (stream == outputStream)
			{
				/*if ([outgoingData length] > 0)
				{
					[outputStream write:(const uint8_t*)[outgoingData bytes] maxLength:[outgoingData length]];
					NSLog(@"%s",[outgoingData bytes]);
					
				 [outgoingData setLength:0];				
				}*/
				
				NSUInteger dataSize = [outgoingData lengthOfBytesUsingEncoding:NSASCIIStringEncoding]; //NSUTF8StringEncoding];
				if (dataSize > 0)
				{
					m_didNotWriteToOutputStream = NO;
					//copy vector contents to buffer
					uint8_t buffer[dataSize];
					
					NSRange range;
					range.location = 0;
					range.length = dataSize;
					//get the bytes to be returned
					//[outgoingData getBytes:buffer maxLength:dataSize usedLength:NULL encoding:NSUTF8StringEncoding options:NSStringEncodingConversionAllowLossy range:range remainingRange:NULL];
					[outgoingData getBytes:buffer maxLength:dataSize usedLength:NULL encoding:NSASCIIStringEncoding options:NSStringEncodingConversionAllowLossy range:range remainingRange:NULL];
					//send buffer to the server				
					NSUInteger bytesWritten = [outputStream write:buffer maxLength:dataSize];
					NSLog(@"%s, bytesWritten = %d",buffer, bytesWritten);
					//erase the bytes that have been sent
					[outgoingData deleteCharactersInRange:range];
					
					m_macConnection->BytesSent(dataSize);
				
				}
				else 
				{
					m_didNotWriteToOutputStream = YES;
				}

			}
		}
		break;
		case NSStreamEventHasBytesAvailable:
		{
			if (stream == inputStream)
			{
				uint8_t buf[1024];
				NSInteger len = [inputStream read:buf maxLength:1024];
				if (len > 0) 
				{
					NSString* data = [[NSString alloc] initWithBytes:buf length:len encoding:NSASCIIStringEncoding];					
					[incomingData appendString:data];
					[data release];
					
					m_macConnection->BytesRead(buf, len);
				} 
				else 
				{
					NSLog(@"no buffer!");
				}			
			}			
		}
		break;	
		case NSStreamEventErrorOccurred:
		{
			NSLog(@"error, outputStream = %@", [stream streamError]);
			
		}
		break;
		case NSStreamEventEndEncountered:
		{
			NSLog(@"end of stream");
		
            [stream close];
            [stream removeFromRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
            [stream release];
            stream = nil;			
		}
		break;
	}	
}

@end

