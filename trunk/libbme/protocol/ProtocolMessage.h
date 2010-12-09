/*
 *  ProtocolMessage.h
 *  Bme
 *
 *  Created by Tim De Jong on 04-05-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef PROTOCOL_MESSAGE_H
#define PROTOCOL_MESSAGE_H

#include <string>
#include <stdint.h>
#include <vector>
#include <map>

class ParsedPayload;

//parses commands, into lines and parameters
class ProtocolMessage
{
private:
	ProtocolMessage();
	bool ParseReceivedString(std::string receivedString);

public:
	static ProtocolMessage*		ProtocolMessageFromString(std::string receivedString);
	static void					Tokenize(const std::string str, std::vector<std::string>& tokens, const std::string delimiters = " ");
	static uint32_t				CurrentTrId();
private:
	static uint32_t				s_trId;	
	
public:	
	ProtocolMessage(std::string commandType);
	virtual ~ProtocolMessage();
	
	void						SetCommandType(std::string commandType);
	std::string					CommandType();
	bool						IsPayloadMessage();
	
	
	bool						HasTrId();
	void						SetTrId(uint32_t trId);
	uint32_t					TrId();//do not use 0 as TrId!
		
	std::vector<std::string>	GetParameters();
	int							ParamCount();
	std::string					GetParam(int index);
	void						SetParam(int index, std::string param);
	void						AddParam(std::string param);
	void						RemoveParam(int index);
	
	uint32_t					PayloadSize();
	bool						HasPayload();
	void						SetPayloadString(std::string payload); 
	std::string					PayloadString();
	void						RemovePayload();
	
	ParsedPayload				Payload();
	
	std::string					ToString();
	
private:
	std::string					m_commandType;
	uint32_t					m_trID;
	std::vector<std::string>	m_parameters;
	std::string					m_payload;
	uint32_t					m_payloadSize;
	bool						m_isPayloadMessage;
		
};

class ParsedPayload
{	
public:
	ParsedPayload();
	ParsedPayload(std::string payloadText);
	virtual ~ParsedPayload();
	
	size_t CountLines();
	
	void AddParamForKey(std::string key, std::string param);
	std::string GetParamForKey(std::string key, int32_t index = 0);
	
	std::vector<std::string> GetParamLine(std::string key);
	std::string ToString();
	
	virtual std::vector<std::string> operator[](std::string key);

private:	
	void ParsePayload(std::string payloadText);
	
private:
	std::vector<std::string> m_orderedPayload;
	std::map<std::string, std::vector<std::string> > m_parsedPayload;
};

#endif

