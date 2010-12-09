/*
 *  MSNP12PingHandler.cpp
 *  Bme
 *
 *  Created by Tim De Jong on 06-07-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */

#include "MSNP12PingHandler.h"
#include "ProtocolConstants.h"
#include "ProtocolMessage.h"
#include "ICrypto.h"
#include "PlatformSpecific.h"
#include <string>
#include <iostream>

MSNP12PingHandler::MSNP12PingHandler()
					:	ProtocolHandler(),
						m_receivedPong(false)
{
}

MSNP12PingHandler::~MSNP12PingHandler()
{
}

bool MSNP12PingHandler::IsHandlerForMessage(ProtocolMessage* message)
{
	std::string command = message->CommandType();
	return (command == NotificationMessages::K_SERVER_PONG) || (command == NotificationMessages::K_SERVER_PING);
}

void MSNP12PingHandler::HandleMessage(ProtocolMessage* message)
{
	std::string command = message->CommandType();
	
	if (command == NotificationMessages::K_SERVER_PONG)
	{
		//server pong notification, still online
		m_receivedPong = true;
	}	 
	else if(command == NotificationMessages::K_SERVER_PING)
	{
		m_receivedPong = false;
		//server challenge, respond to it
		std::string challenge = message->GetParam(0);
								
		//find responseHash
		cout << "challenge" << challenge << endl;						
		std::string response = this->DoMSNP11Challenge(challenge);							
		cout << "response" << response << endl;						
		//construct response				
 		ProtocolMessage *pongMessage = new ProtocolMessage(NotificationMessages::K_CLIENT_PONG);
		pongMessage->AddParam(ProtocolConstants::K_MSN7_PRODUCT_ID); 					
		pongMessage->SetPayloadString(response);
				
		this->SendCommandMessageTrId(pongMessage);	//TODO: check why message isn't sent			
	}
}

/**case PingHandler::K_PING_MSG:
 {
 if (m_receivedPong)
 {
 m_receivedPong = false;
 //construct ping message
 BMessage *pingMessage = new BMessage(ProtocolConstants::K_ADD_COMMAND_MESSAGE);
 pingMessage->AddString(K_COMMAND,NotificationMessages::K_CLIENT_PING);
 //send ping(add to NSLoopers MessageQueue
 SendCommandMessage(pingMessage);
 }
 else
 {
 //user disconnected, notify user
 BMessage msg(InterfaceMessages::K_USER_SIGNED_OUT_MSG);
 SendCommandMessage(&msg);
 }			
 }
 break;
*/

//code from: http://msnpiki.msnfanatic.com/index.php/MSNP11:Challenges
std::string MSNP12PingHandler::DoMSNP11Challenge(std::string challenge) 
{
	//Step 1:The MD5 Hash
	IMD5* md5 = PlatformSpecific::GetCrypto()->GetMD5();
	md5->Init();
	md5->Update((unsigned char *)challenge.c_str(), challenge.size());
	md5->Update((unsigned char *)(ProtocolConstants::K_MSN7_PRODUCT_KEY).c_str(), (ProtocolConstants::K_MSN7_PRODUCT_KEY).size());
	
	unsigned char pMD5Hash[16];
	md5->Final(pMD5Hash);
		
	
	int pMD5Parts[4];	
	memcpy(pMD5Parts,pMD5Hash,16);
	
	for (int i = 0; i < 4; i++) 
	{
		pMD5Parts[i] &= 0x7FFFFFFF;
	}
	//Step 2: A new String
	int nchlLen = challenge.size() + ProtocolConstants::K_MSN7_PRODUCT_ID.size();
	if (nchlLen % 8 != 0)
		nchlLen += 8 - (nchlLen % 8);
	
	char *chlString = new char[nchlLen];
	memset(chlString, '0', nchlLen);
	memcpy(chlString, challenge.c_str(), challenge.size());
	memcpy(chlString + challenge.size(), ProtocolConstants::K_MSN7_PRODUCT_ID.c_str(), ProtocolConstants::K_MSN7_PRODUCT_ID.size());
	int *pchlStringParts = (int*)chlString;
	
	//Step 3: The 64 bit key
	long long nHigh=0;
	long long nLow=0;
	
	for (int i = 0; i < (nchlLen/4) - 1; i += 2) 
	{
		long long temp = pchlStringParts[i];
		temp = (pMD5Parts[0] * (((0x0E79A9C1 * (long long)pchlStringParts[i]) % 0x7FFFFFFF) + nHigh) + pMD5Parts[1]) % 0x7FFFFFFF;
		
		nHigh = (pMD5Parts[2] * (((long long)pchlStringParts[i+1] + temp) % 0x7FFFFFFF) + pMD5Parts[3]) % 0x7FFFFFFF;
		
		nLow = nLow + nHigh + temp;
	}
	nHigh = (nHigh + pMD5Parts[1]) % 0x7FFFFFFF;
	nLow = (nLow + pMD5Parts[3]) % 0x7FFFFFFF;
	
	delete[] chlString;
	//Step 4: Using the key
	uint32_t *pNewHash = (uint32_t*)pMD5Hash;
	
	pNewHash[0] ^= nHigh;
	pNewHash[1] ^= nLow;
	pNewHash[2] ^= nHigh;
	pNewHash[3] ^= nLow;
	
	char hash[33];
	//convert resulting hash to hexadecimal?
	char szHexChars[]="0123456789abcdef";
	for (int i = 0; i < 16; i++) 
	{
		hash[i*2] = szHexChars[(pMD5Hash[i] >> 4) & 0xF];
		hash[(i*2)+1] = szHexChars[pMD5Hash[i] & 0xF];
	}
	hash[32] = '\0';
	
	std::string response(hash);
	//clean up the object, we do not need it anymore*/
	delete md5;
	return response;
}
