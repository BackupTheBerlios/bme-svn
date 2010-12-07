/*
 *  ProtocolMessage.cpp
 *  Bme
 *
 *  Created by Tim De Jong on 04-05-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */

#include "ProtocolMessage.h"
#include "ProtocolConstants.h"
#include "Common.h"
#include <sstream>
#include <cstdlib>
#include <iostream>

uint32_t ProtocolMessage::s_trId = 0;

ProtocolMessage* ProtocolMessage::ProtocolMessageFromString(std::string receivedString)
{
	ProtocolMessage* message = new ProtocolMessage();
	if (message->ParseReceivedString(receivedString))
	{
		return message;
	}
	return NULL;
}

uint32_t ProtocolMessage::CurrentTrId()
{
	uint32_t newTr = s_trId + 1;
	if (newTr > 0 && newTr <= ProtocolConstants::K_MAX_TR_ID)
	{	
		s_trId++;
	}
	else
	{
		//reset the counter
		s_trId = 0;
	}
	return s_trId;
}

//Constructor and methods
ProtocolMessage::ProtocolMessage()
					:	m_commandType(""),
						m_trID(0),
						m_payload(""),
						m_payloadSize(0),
						m_isPayloadMessage(false)
{
}

ProtocolMessage::ProtocolMessage(std::string commandType)
					:	m_commandType(commandType),
						m_trID(0),
						m_payload(""),
						m_payloadSize(0),
						m_isPayloadMessage(false)
{
}

ProtocolMessage::~ProtocolMessage()
{
}

bool ProtocolMessage::ParseReceivedString(std::string receivedString)
{
	std::string breakDelimiter = "\r\n";
	size_t delimiterPosition = receivedString.find(breakDelimiter);
	//if the break was found, this means that the string contains a payload part
	if (delimiterPosition != std::string::npos)
	{
		//split the string in the payload and the message part
		std::string payload = receivedString.substr(delimiterPosition + breakDelimiter.length());
		this->SetPayloadString(payload);
		//message part is the part before the break delimiter
		receivedString = receivedString.substr(0, delimiterPosition);
	}	
	//parse first line of the message into separate tokens
	std::string delimiter = " ";
	std::vector<std::string> tokens;
	ProtocolMessage::Tokenize(receivedString, tokens, delimiter);
	if (tokens.size() > 0)
	{
		//get first token, which is the command type
		std::string command = tokens[0];
		this->SetCommandType(command);
		//erarse from the list of tokens still being parsed
		tokens.erase(tokens.begin());		
		//check if this command is a payload message
		int numberOfPayloadCommands = sizeof(ProtocolConstants::K_PAYLOAD_COMMANDS) / sizeof(ProtocolConstants::K_PAYLOAD_COMMANDS[0]);
		for (int i = 0; i < numberOfPayloadCommands; i++)
		{
			std::string payloadCommand = ProtocolConstants::K_PAYLOAD_COMMANDS[i];
			if (CommandType() == payloadCommand)
			{
				m_isPayloadMessage = true;
				break;
			}
		}
		//check if the second token is a trId, token is at begin of the vector because we removed the command token
		std::string trId = tokens[0];
		//if the token is a number it is a trId
		if (Common::is_number(trId))
		{
			//convert the trId to an int
			this->SetTrId(atoi(trId.c_str()));
			//erase the trId
			tokens.erase(tokens.begin());
		}		
		//check if the last token is a payload size (should be payload message then)
		if (IsPayloadMessage())
		{
			//get last element in token vector
			std::string payloadSize = tokens.back();
			//find out if it is a number
			if (Common::is_number(payloadSize))
			{
				m_payloadSize = atoi(payloadSize.c_str());
				//remove last token from the tokens still being parsed 
				tokens.erase(tokens.end() - 1);
			}			
			else 
			{
				//payload size not found
				m_isPayloadMessage = false;
			}
		}
		//go through rest of the tokens, and add them as parameters
		typedef std::vector<std::string>::const_iterator TI;
		for (TI t = tokens.begin(); t != tokens.end(); ++t)
		{
			this->AddParam(*t);
		}
		return true;
	}
	return false;
}

void ProtocolMessage::SetCommandType(std::string commandType)
{
	m_commandType = commandType;
}

std::string ProtocolMessage::CommandType()
{
	return m_commandType;
}

bool ProtocolMessage::IsPayloadMessage()
{
	return m_isPayloadMessage;
}

bool ProtocolMessage::HasTrId()
{
	return (m_trID > 0);
}

void ProtocolMessage::SetTrId(uint32_t trId)
{
	m_trID = trId;
}

uint32_t ProtocolMessage::TrId()
{
	return m_trID;
}

std::vector<std::string> ProtocolMessage::GetParameters()
{
	return m_parameters;
}

int	ProtocolMessage::ParamCount()
{
	return m_parameters.size();
}

std::string ProtocolMessage::GetParam(int index)
{
	return m_parameters[index];
}

void ProtocolMessage::SetParam(int index, std::string param)
{
	m_parameters[index] = param;
}

void ProtocolMessage::AddParam(std::string param)
{
	m_parameters.push_back(param);
}

void ProtocolMessage::RemoveParam(int index)
{
	m_parameters.erase(m_parameters.begin() + index);
}

uint32_t ProtocolMessage::PayloadSize()
{
	return m_payloadSize;
}

bool ProtocolMessage::HasPayload()
{
	return (this->PayloadSize() > 0);
}

void ProtocolMessage::SetPayloadString(const std::string payload)
{
	m_payload = payload;
	m_payloadSize = m_payload.size();
	m_isPayloadMessage = true;
}

std::string	ProtocolMessage::PayloadString()
{
	return m_payload;
}

void ProtocolMessage::RemovePayload()
{
	m_payload = "";
	m_isPayloadMessage = false;
}

ParsedPayload ProtocolMessage::Payload()
{
	return ParsedPayload(this->PayloadString());
}

std::string	ProtocolMessage::ToString()
{	
	//start message with command type
	std::string messageString = this->CommandType();
	//add trId if available
	if (this->HasTrId())
	{		
		std::stringstream ss;
		ss << " " << this->TrId();
		messageString += ss.str(); 
	}
	//add parameters for message
	typedef std::vector<std::string>::const_iterator PI;
	for (PI param = m_parameters.begin(); param != m_parameters.end(); ++param)
	{
		messageString += " " + (*param);
	}
	
	//add payloadsize and payload if available
	if (this->HasPayload())
	{		
		std::stringstream ss;
		//add payload size, separator, and payload
		ss << " " << this->PayloadSize() << "\r\n" << this->PayloadString();
		//add to the message string
		messageString += ss.str(); 
	}
	else 
	{
		//no payload, end message with the separator
		messageString += "\r\n";
	}
	
	return messageString;
}

void ProtocolMessage::Tokenize(const std::string str, std::vector<std::string>& tokens, const std::string delimiters)
{
    // Skip delimiters at beginning.
    std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    std::string::size_type pos     = str.find_first_of(delimiters, lastPos);
	
    while (std::string::npos != pos || std::string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}

ParsedPayload::ParsedPayload()
{
}

ParsedPayload::ParsedPayload(std::string payloadText)
{
	this->ParsePayload(payloadText);
}

ParsedPayload::~ParsedPayload()
{	
}

size_t ParsedPayload::CountLines()
{
	return m_orderedPayload.size();
}

void ParsedPayload::AddParamForKey(std::string key, std::string param)
{
	//vector to keep the key in the order they were added
	//this is used to output the items in the correct order in ToString()
	if (m_parsedPayload[key].size() == 0)
	{		
		m_orderedPayload.push_back(key);
	}
	m_parsedPayload[key].push_back(param);
}

std::string ParsedPayload::GetParamForKey(std::string key, int32_t index)
{
	return m_parsedPayload[key].at(index);
}

std::vector<std::string> ParsedPayload::GetParamLine(std::string key)
{
	return m_parsedPayload[key];
}

//TODO: fix (double) space issue
std::string ParsedPayload::ToString()
{
	typedef std::vector<std::string>::const_iterator PI;
	typedef std::vector<std::string>::const_iterator VI;
	
	std::string payloadString;
	
	for (VI m = m_orderedPayload.begin(); m != m_orderedPayload.end(); ++m)
	{
		std::string key = (*m);
		payloadString += key + ":";  
		std::vector<std::string> paramLine = m_parsedPayload[key];
		
		int i = 0;
		for (PI p = paramLine.begin(); p != paramLine.end(); ++p)
		{
			payloadString += " " + *p;
			//last parameter should end with endline separator
			if (i == (paramLine.size() - 1))
			{
				payloadString += "\r\n";
			}
			else
			{
				//otherwise separate parameters with semicolons
				payloadString += ";";
			}
			
			i++;
		}
	}
	return payloadString;
}

//TODO: handle double breaks
void ParsedPayload::ParsePayload(std::string payloadText)
{
	std::string breakDelimiter = "\r\n";
	std::string keySeparator = ":";
	std::string paramSeparator = ";";
	
	//loop through the payload line by line
	size_t startPosition = 0;
	size_t delimiterPosition = payloadText.find(breakDelimiter);
	while (startPosition < payloadText.size())
	{
		//get the current line
		std::string currentLine = payloadText.substr(startPosition, delimiterPosition - startPosition);
		//parse line
		size_t keySeparatorPos = currentLine.find(keySeparator); 
		std::string key = currentLine.substr(0, keySeparatorPos);
		
		size_t startPos = keySeparatorPos + 1;
		do 
		{
			size_t paramPos = currentLine.find(paramSeparator,startPos);
			if (paramPos == std::string::npos)
			{
				//if no parameter separator has been found, get the text till the end of the line
				paramPos = currentLine.size();			
			}			
			std::string param = currentLine.substr(startPos, paramPos - startPos);
			//add parameter for key
			this->AddParamForKey(Common::truncString(key), Common::truncString(param));
					
			startPos = paramPos + 1;
		} 
		while (startPos < currentLine.size());
		
		//move current delimiter position
		startPosition = delimiterPosition + breakDelimiter.size();
		//find next break
		delimiterPosition = payloadText.find(breakDelimiter, startPosition);
	}
}

std::vector<std::string> ParsedPayload::operator[](std::string key)
{
	return this->GetParamLine(key);
}
