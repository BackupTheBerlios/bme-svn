/*
 *  MSNP12AuthenticationProtocol.cpp
 *  Bme
 *
 *  Created by Tim De Jong on 23-06-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */

#include "MSNP12UserProtocol.h"
#include "ProtocolConstants.h"
#include "Common.h"
#include "PlatformSpecific.h"
#include "ISSLConnection.h"
#include <iostream>
#include <sstream>

MSNP12UserProtocol::MSNP12UserProtocol()
						:	ProtocolHandler(),
							IUserProtocol(),
							m_username(""),
							m_password(""),
							m_initialStatus(new Status())
{
}


MSNP12UserProtocol::MSNP12UserProtocol(std::string username, std::string password)
								:	ProtocolHandler(),
									IUserProtocol(),
									m_username(username),
									m_password(password),
									m_initialStatus(new Status())
{
}

MSNP12UserProtocol::~MSNP12UserProtocol()
{
}

bool MSNP12UserProtocol::IsHandlerForMessage(ProtocolMessage* message)
{
	std::string command = message->CommandType();
	return (	command == NotificationMessages::K_PROTOCOLS_SUPPORTED ||
				command == NotificationMessages::K_CLIENT_INFORMATION ||
				command == NotificationMessages::K_NS_DOWN ||
				command == NotificationMessages::K_NS_USR_COMMAND ||
				command == NotificationMessages::K_PHONE_NUMBERS ||
				command == NotificationMessages::K_NS_PAYLOAD_MSG);
}

void MSNP12UserProtocol::HandleMessage(ProtocolMessage* message)
{
	std::string command = message->CommandType();
	if (command == NotificationMessages::K_PROTOCOLS_SUPPORTED)
	{
		//received an answer to our VER message
		//check if our protocol is supported!
		bool protocolSupported = false;
		for(int i = 0; i < message->ParamCount(); i++)
		{
			std::string remainingMsg = message->GetParam(i);
			//is our protocol supported?
			if (remainingMsg == ProtocolConstants::K_PROTOCOL_VERSION)
			{
				
				protocolSupported = true;
				break;
			}					
		}
		
		if (protocolSupported)
		{
			//construct next message (CVR)
			ProtocolMessage *cvrMessage = new ProtocolMessage(NotificationMessages::K_CLIENT_INFORMATION);
			
			cvrMessage->AddParam("0x0409 win");
			cvrMessage->AddParam(ProtocolConstants::K_WINDOWS_XP_SP2_VERSION);
			cvrMessage->AddParam("i386 MSNMSGR"); 
			cvrMessage->AddParam(ProtocolConstants::K_MSN_VERSION);
			cvrMessage->AddParam("MSMSGS");
			cvrMessage->AddParam(m_username);
			
			SendCommandMessageTrId(cvrMessage);						
		}
		else
		{
			//error, protocol used by Bme not supported
			/*BAlert *alert = new BAlert("Error","Bme's using an old protocol not supported by the current MSN servers","OK",NULL,NULL,B_WIDTH_AS_USUAL,B_WARNING_ALERT);
			alert->Go();*/
		}
	}
	else if (command == NotificationMessages::K_CLIENT_INFORMATION)
	{
		//received an answer to our CVR message							
		ProtocolMessage *usrMessage = new ProtocolMessage(NotificationMessages::K_NS_USR_COMMAND);
				
		//send initial USR
		usrMessage->AddParam("TWN");				
		usrMessage->AddParam("I");
		usrMessage->AddParam(m_username);
		
		SendCommandMessageTrId(usrMessage);				
	}
	else if (command == NotificationMessages::K_NS_DOWN)
	{
		//received XFR command 
		std::string nsString = message->GetParam(0);
		if (nsString == "NS")
		{
			//reroute to NS server
			std::string nsServerAddress = message->GetParam(1);
			//separate Notification Server address and port
			size_t colonIndex = nsServerAddress.find(":");
			int nsPort;							
			if (colonIndex != std::string::npos)
			{
				std::string nsPortString = nsServerAddress.substr(colonIndex + 1,nsServerAddress.size() - colonIndex);
				nsPort = atoi(nsPortString.c_str());
				nsServerAddress.erase(colonIndex,nsServerAddress.size() - colonIndex);	
				//need to connect to another server, close existing connection
				ServerConnection* serverConnection = this->GetServerConnection();
				serverConnection->Close();
				//connect to Notification Server, reconnect to different server!
				serverConnection->Connect(nsServerAddress,nsPort);
				StartLogin(m_username, m_password);				
			}
		}
		else if (nsString == "SB")
		{
			//TODO: create a new SBServerConnection here???
			//HandleSwitchboard(message);
			//connect to new server suggested
		}	
	}
	else if (command == NotificationMessages::K_NS_USR_COMMAND)
	{
		//one of the USR commands, check which one
		std::string usrFirstString = message->GetParam(0);
		
		if (usrFirstString == "TWN")
		{
			std::string challenge = message->GetParam(2);
								
			//still authenticating 
			std::string ticket = this->TweenerAuthenticate(challenge);
			if	(!ticket.empty())
			{
				//respond to command with proper ticket						
				ProtocolMessage *usrReply = new ProtocolMessage(NotificationMessages::K_NS_USR_COMMAND);
								
				usrReply->AddParam("TWN");
				usrReply->AddParam("S");
				usrReply->AddParam(ticket);							
			
				SendCommandMessageTrId(usrReply);		
			}
			else 
			{
				//error authenticating
				cout << "Error authenticating: no ticket" << endl;
			}

		}
		else if (usrFirstString == "OK")
		{
			//authentication completed! Change to contact view and set displayname
			std::string displayName = message->GetParam(2);
										
			//convert displayname from URL-encoded string to normal Be String
			displayName = Common::decodeURL(displayName);//???
						
			//notify protocol that the authentication process has been completed
			this->ProtocolDelegate()->AuthenticationCompleted();				
			
		}		
	}
	else if (command == NotificationMessages::K_PHONE_NUMBERS)
	{
		std::string subCommand = message->GetParam(0);
		
		if (subCommand == SettingTypes::K_MY_FRIENDLY_NAME)
		{
			std::string username = Common::decodeURL(message->GetParam(1));
			m_userProtocolDelegate->UsernameFound(username);
		}
		else if (subCommand == SettingTypes::K_HOME_PHONE_NUMBER)
		{
			std::string phoneNumber = Common::decodeURL(message->GetParam(1));
			m_userProtocolDelegate->PhoneNumberFound(K_HOME_PHONE_NUMBER, phoneNumber);			
		}
		else if (subCommand == SettingTypes::K_WORK_PHONE_NUMBER)
		{
			std::string phoneNumber = Common::decodeURL(message->GetParam(1));
			m_userProtocolDelegate->PhoneNumberFound(K_WORK_PHONE_NUMBER, phoneNumber);			
		}
		else if (subCommand == SettingTypes::K_MOBILE_PHONE_NUMBER)
		{
			std::string phoneNumber = Common::decodeURL(message->GetParam(1));
			m_userProtocolDelegate->PhoneNumberFound(K_MOBILE_PHONE_NUMBER, phoneNumber);			
		}
		else if (subCommand == SettingTypes::K_HAS_MSN_SPACE_BLOG)
		{
			bool hasBlog = atoi(message->GetParam(1).c_str());
			m_userProtocolDelegate->BlogSettingFound(hasBlog);	
		}
		else if (subCommand == SettingTypes::K_CAN_PAGE_MOBILE) 
		{
			std::string value = Common::decodeURL(message->GetParam(1));
			if (value == "Y")
			{
				m_userProtocolDelegate->CanPageSettingFound(true);
			}
		}
		else if (subCommand == SettingTypes::K_CAN_DIRECT_PAGE_MOBILE)
		{
			std::string value = Common::decodeURL(message->GetParam(1));
			if (value == "2")
			{
				m_userProtocolDelegate->MSNDirectCapableSettingFound(true);
			}
			else 
			{
				m_userProtocolDelegate->MSNDirectCapableSettingFound(false);
			}

		}
		else if (subCommand == SettingTypes::K_HAS_MOBILE_DEVICE_ENABLED)
		{
			std::string value = Common::decodeURL(message->GetParam(1));
			if (value == "Y")
			{
				m_userProtocolDelegate->HasMobileDeviceEnabledSettingFound(true);
			}
			else
			{
				m_userProtocolDelegate->HasMobileDeviceEnabledSettingFound(false);
			}
		}
	}
	else if (command == NotificationMessages::K_NS_PAYLOAD_MSG)
	{
		ParsedPayload payload = message->Payload();
		cout << "Payload= " << payload.ToString() << endl;
	}
}

void MSNP12UserProtocol::SendInitialPresence()
{
	ProtocolMessage* pingMessage = new ProtocolMessage(NotificationMessages::K_CLIENT_PING);
	SendCommandMessage(pingMessage);	
	
	//set initial presence
	ProtocolMessage *initialPresenceMsg = new ProtocolMessage(NotificationMessages::K_CHANGE_STATUS);
	initialPresenceMsg->AddParam(m_initialStatus->GetAbbreviation());
	//find client ID 
	
	int64_t bmeId = ClientIdentification::K_MSNC4;
	cout << "id= " << bmeId << endl;
	
	std::stringstream ss;
	ss << bmeId;
	std::string clientID = ss.str(); 
	//add client ID to the initial presence message
	initialPresenceMsg->AddParam(clientID);
	//add msn object!
	
	//send initial presence message to the server
	SendCommandMessageTrId(initialPresenceMsg);
}

	//figure out what to do with this one
void MSNP12UserProtocol::StartLogin(std::string username, std::string password)
{
	//send first command message(VER)
	ProtocolMessage* message = new ProtocolMessage(NotificationMessages::K_PROTOCOLS_SUPPORTED);
	message->AddParam(ProtocolConstants::K_PROTOCOL_VERSION);				
	message->AddParam("CVR0");				
	SendCommandMessageTrId(message);
}

void MSNP12UserProtocol::Logout()
{
	ProtocolMessage* message = new ProtocolMessage(NotificationMessages::K_NS_LOG_OFF);
	SendCommandMessage(message);
}

void MSNP12UserProtocol::SetLoginDetails(std::string username, std::string password)
{
	m_username = username;
	m_password = password;
}

std::string	MSNP12UserProtocol::TweenerAuthenticate(std::string challenge)
{
	std::string ticket;	
	std::string passPortNexusAddress = "nexus.passport.com";
	
	HTTPFormatter *send = new HTTPFormatter(passPortNexusAddress.c_str(),"/rdr/pprdr.asp");
	//cout << send->Flatten() << endl;
	HTTPFormatter *recv = NULL;
	
	if (this->SSLSend(passPortNexusAddress, send, &recv))
	{
		//cout << "ssl connection" << endl;
		//cout << recv->Flatten() << endl;
		//check if reply is 200 OK
		if (recv->Status() == 200)
		{
			std::string passportUrl = recv->HeaderContents("PassportURLs");		
			std::string loginKey = "DALogin=";
			size_t loginIndex = passportUrl.find(loginKey);
			//find login url in received header
			if (loginIndex != std::string::npos)
			{
				loginIndex += loginKey.size();
				size_t commaIndex = passportUrl.find_first_of(",",loginIndex);
				if (commaIndex != std::string::npos)
				{
					std::string loginUrl = passportUrl.substr(loginIndex, commaIndex - loginIndex);				
					//we do not need the first answer of the server
					delete recv;
					//find host and document parts of login url					
					int16_t status = 0;
					do
					{
						size_t slashIndex = loginUrl.find_first_of("/");
						if (slashIndex != std::string::npos)
						{
							std::string httpsString = "https://";
							//find the index of the https:// in the loginUrl
							size_t httpsIndex = loginUrl.find(httpsString);
							size_t startIndex = 0;
							if (httpsIndex != std::string::npos)
							{
								//calculate the end of the https:// part of the message
								startIndex = httpsIndex + httpsString.size();
							}
							
							std::string hostString = loginUrl.substr(startIndex, slashIndex - startIndex);							
							std::string documentString = loginUrl.substr(slashIndex, loginUrl.size() - slashIndex);							
							//construct a new request to the passport nexus with necessary information
							std::string authorisationHeader = "Passport1.4 OrgVerb=GET,OrgURL=http%3A%2F%2Fmessenger%2Emsn%2Ecom,sign-in=";
							authorisationHeader += Common::encodeURL(m_username);
							authorisationHeader += ",pwd=" + Common::encodeURL(m_password) + ",";
							authorisationHeader += challenge;
							//set new host for request
							send->SetHost(hostString.c_str());
							//set new document for request
							send->SetDocument(documentString.c_str());
							//add authorisation info to header
							send->AddHeader("Authorization", authorisationHeader.c_str());	
							/*send->AddHeader("User-Agent", "MSMSGS");
							send->AddHeader("Connection", "Keep-Alive");
							send->AddHeader("Cache-Control", "no-cache");*/
							
							if (this->SSLSend(hostString, send, &recv))
							{
								status = recv->Status();
								//three possible answers from the server are possible
								if (status == 200)
								{
									//response 200 OK, a header with the requested info has been sent back!
									//get ticket
									std::string authHeader = recv->HeaderContents("Authentication-Info");
									//when authentication key field has not been found check for WWW-Authenticate!
									if (authHeader == "")
										authHeader = recv->HeaderContents("WWW-Authenticate");									
									
									size_t ticketIndex = authHeader.find_first_of("'");
									if (ticketIndex != std::string::npos)
									{							
										ticketIndex++;
										size_t ticketEndIndex = authHeader.find_first_of("'", ticketIndex);
										ticket = authHeader.substr(ticketIndex, ticketEndIndex - ticketIndex);							
									}
									else
									{
										cout << "ticket not found" << endl;
									}
								}
								else if (status == 302)
								{
									//client has to be redirected!																		
									loginUrl = recv->HeaderContents("Location");//TODO: redirection?									
								}
								else if (status == 401)
								{
									//unauthorised, failure! 
									std::string authHeader = recv->HeaderContents("Authentication-Info");
									//when authentication key field has not been found check for WWW-Authenticate!
									if (authHeader == "")
										authHeader = recv->HeaderContents("WWW-Authenticate");
									//Get error message!
									std::string errTxtKey = "cbtxt=";
									size_t errTxtIndex = authHeader.find_first_of(errTxtKey);
									//cout << recv->Flatten() << endl;
									if (errTxtIndex != std::string::npos)
									{
										errTxtIndex += errTxtKey.size();										
										//get the error message
										std::string errorMsg =	authHeader.substr(errTxtIndex, authHeader.size() - errTxtIndex);
										errorMsg = Common::decodeURL(errorMsg);
										//display alert with error!
										/*BAlert *alert = new BAlert("A critical error occurred!",errorMsg.String(),"Ok", NULL, NULL, B_WIDTH_AS_USUAL, B_INFO_ALERT);
										alert->Go();	*/	
										//call authentication failed??
									}									
								}
								else
								{
									cout << "error!" << endl;
								}
								//got the information we need
								delete recv;
							}							
						}
					}
					while (status == 302);
				}
				else
				{
					cout << "comma not found" << endl;
				}			
			}
			else
			{
				cout << "login url not found" << endl;
			}
		}
		else
		{
			cout << "response isn't 200 OK " << endl;
		}
	}
	else
	{
		cout << "login error" << endl;
	}
	delete send;	
	
	return ticket;
}

//inspired by IMkit code, TODO: drop this code and move it to the method above
bool MSNP12UserProtocol::SSLSend(std::string host, HTTPFormatter *send, HTTPFormatter **recv) 
{	
	int32_t port = 443;	
	ISSLConnection* sslConnection = PlatformSpecific::GetConnectionManager()->OpenSSLConnection(host, port, IConnection::K_SSL_V2_SECURITY);
	sslConnection->AddConnectionListener(this);
	
	bool sent = false;
	if (sslConnection)
	{						
		cout << "send: " << send->Flatten() << endl;
		sslConnection->WriteBytes((uint8_t*)send->Flatten(), send->Length());	//TODO:move to didconnect?
	}
	//delete sslConnection; //TODO: move elsewhere, in DidDisconnect?
	
	return sent;
}

void MSNP12UserProtocol::DidConnect()
{		
}

void MSNP12UserProtocol::BytesSent(IConnection* connection, size_t length)
{
}

void MSNP12UserProtocol::BytesRead(IConnection* connection, uint8_t* bytes, size_t length)
{
	std::string readString = "";
	if (length > 0)
	{					
		readString += (char*)bytes;
		readString += '\0'; //TODO:test!
		HTTPFormatter* recv = new HTTPFormatter(readString.c_str(), length);	
		//inform the class that we received bytes from the ssl connection
		
	}
	//close connection
	connection->Close(); 
}

//User protocol methods
void MSNP12UserProtocol::SetInitialStatus(Status* status)
{
	if (status->IsUserChoice())
	{
		m_initialStatus = status;
	}
}

void MSNP12UserProtocol::SetStatus(Status* status)
{
	if (status->IsUserChoice())
	{
	}
}

//TODO:check server answer to see if the display name has been set correctly
void MSNP12UserProtocol::SetDisplayName(std::string displayName)
{
	ProtocolMessage* protocolMessage = new ProtocolMessage(NotificationMessages::K_PHONE_NUMBERS);
	protocolMessage->AddParam(SettingTypes::K_MY_FRIENDLY_NAME);
	protocolMessage->AddParam(Common::encodeURL(displayName));	
	this->SendCommandMessageTrId(protocolMessage);	
}

void MSNP12UserProtocol::SetPersonalMessage(std::string personalMessage)
{
}

void MSNP12UserProtocol::SetMusicPlaying(std::string musicPlaying)
{
}

//TODO: check server answer to see if the phonenumbers have been set correctly + settings for mobile paging
void MSNP12UserProtocol::AddPhoneNumber(PhoneNumberType phoneType, std::string phoneNumber)
{
	switch (phoneType) 
	{
		case K_HOME_PHONE_NUMBER:
		{
			ProtocolMessage* protocolMessage = new ProtocolMessage(NotificationMessages::K_PHONE_NUMBERS);
			protocolMessage->AddParam(SettingTypes::K_HOME_PHONE_NUMBER);
			protocolMessage->AddParam(Common::encodeURL(phoneNumber));
			this->SendCommandMessageTrId(protocolMessage);
		}
		break;
		case K_WORK_PHONE_NUMBER:
		{
			ProtocolMessage* protocolMessage = new ProtocolMessage(NotificationMessages::K_PHONE_NUMBERS);
			protocolMessage->AddParam(SettingTypes::K_WORK_PHONE_NUMBER);
			protocolMessage->AddParam(Common::encodeURL(phoneNumber));
			this->SendCommandMessageTrId(protocolMessage);
		}
		break;
		case K_MOBILE_PHONE_NUMBER:
		{
			ProtocolMessage* protocolMessage = new ProtocolMessage(NotificationMessages::K_PHONE_NUMBERS);
			protocolMessage->AddParam(SettingTypes::K_MOBILE_PHONE_NUMBER);
			protocolMessage->AddParam(Common::encodeURL(phoneNumber));
			this->SendCommandMessageTrId(protocolMessage);
		}
		break;	
	}
}

void MSNP12UserProtocol::SetUserProtocolDelegate(IUserProtocolDelegate* userProtocolDelegate)
{
	m_userProtocolDelegate = userProtocolDelegate;
}

IUserProtocolDelegate* MSNP12UserProtocol::Delegate()
{
	return m_userProtocolDelegate;
}


