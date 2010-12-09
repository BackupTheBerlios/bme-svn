/*
 *  XMLNode.h
 *  BmeApp
 *
 *  Created by Tim De Jong on 26-08-10.
 *  Copyright 2010 ThinkPractice. All rights reserved.
 *
 */
#ifndef XML_NODE_H
#define XML_NODE_H

#include <string>
#include <vector>

using namespace std;

class XMLDocument;

class XMLNode
{
public:
	enum XMLNodeKind
	{
		XMLInvalidKind = 0,
		XMLDocumentKind,
		XMLElementKind,
		XMLAttributeKind,
		XMLNamespaceKind,
		XMLProcessingInstructionKind,
		XMLCommentKind,
		XMLTextKind,
		XMLDTDKind,
		XMLEntityDeclarationKind,
		XMLAttributeDeclarationKind,
		XMLElementDeclarationKind,
		XMLNotationDeclarationKind
	};
		
public:
	XMLNode();
	XMLNode(XMLNodeKind xmlNodeKind);
	virtual ~XMLNode();	
	
	virtual size_t				Index();
	virtual XMLNodeKind			Kind();
	virtual size_t				Level();
	virtual void				SetName(std::string name);
	virtual string				Name();
	virtual void				SetStringValue(std::string value);
	virtual	string				StringValue();	
	
	virtual XMLDocument*		RootDocument();
	virtual XMLNode*			Parent();
	
	virtual void				AddChild(XMLNode* child);
	virtual XMLNode*			ChildAtIndex(size_t index);
	virtual size_t				ChildCount();
	virtual vector<XMLNode*>	Children();
	virtual XMLNode*			NextNode();
	virtual XMLNode*			NextSibling();
	virtual XMLNode*			PreviousNode();
	virtual XMLNode*			PreviousSibling();
	
	virtual string				XMLString();	

public:
	virtual void				SetIndex(size_t index);
	virtual void				SetKind(XMLNodeKind kind);
	virtual void				SetLevel(size_t level);
	virtual void				SetRootDocument(XMLDocument* rootDocument);
	virtual void				SetParent(XMLNode* parent);
	virtual void				SetNextNode(XMLNode* nextNode);
	virtual void				SetPreviousNode(XMLNode* previousNode);	
	virtual void				SetXMLString(string xmlString);
	
protected:
	size_t						m_index;
	XMLNodeKind					m_xmlNodeKind;
	size_t						m_level;
	string						m_name;
	string						m_stringValue;
	
	XMLDocument*				m_rootDocument;
	XMLNode*					m_parent;
	XMLNode*					m_nextNode;
	XMLNode*					m_previousNode;
	
	vector<XMLNode*>			m_children;
	
	string						m_xmlString;
};

#endif
