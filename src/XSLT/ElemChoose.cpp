/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 1999 The Apache Software Foundation.  All rights 
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer. 
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:  
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "Xalan" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written 
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation and was
 * originally based on software copyright (c) 1999, International
 * Business Machines, Inc., http://www.ibm.com.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */
#include "ElemChoose.hpp"



#include <sax/AttributeList.hpp>
#include <sax/SAXException.hpp>



#include <XPath/XObjectFactory.hpp>
#include <XPath/XPath.hpp>



#include "Constants.hpp"
#include "ElemWhen.hpp"
#include "SelectionEvent.hpp"
#include "Stylesheet.hpp"
#include "StylesheetConstructionContext.hpp"
#include "StylesheetExecutionContext.hpp"
#include "StylesheetRoot.hpp"



ElemChoose::ElemChoose(
			StylesheetConstructionContext&	constructionContext,
			Stylesheet&						stylesheetTree,
			const AttributeList&			atts,
			int								lineNumber,
			int								columnNumber) :
	ElemTemplateElement(constructionContext,
						stylesheetTree,
						lineNumber,
						columnNumber,
						Constants::ELEMNAME_CHOOSE)
{
	const unsigned int	nAttrs = atts.getLength();

	for(unsigned int i = 0; i < nAttrs; i++)
	{
		const XalanDOMChar*	const	aname = atts.getName(i);

		if(isAttrOK(aname, atts, i, constructionContext) == false ||
		   processSpaceAttr(aname, atts, i, constructionContext))
		{
			constructionContext.error(
				"xsl:choose has an illegal attribute",
				0,
				this);
		}
	}	
}



const XalanDOMString&
ElemChoose::getElementName() const
{
	return Constants::ELEMNAME_CHOOSE_WITH_PREFIX_STRING;
}



void
ElemChoose::execute(StylesheetExecutionContext&		executionContext) const
{
	ElemTemplateElement::execute(executionContext);

	XalanNode* sourceNode = executionContext.getCurrentNode();

    for (const ElemTemplateElement* node = getFirstChildElem();
			node != 0;
				node = node->getNextSiblingElem()) 
    {
		const int	type = node->getXSLToken();

		if(Constants::ELEMNAME_WHEN == type)
		{
			const ElemWhen* when = 
#if defined(XALAN_OLD_STYLE_CASTS)
				(const ElemWhen*)node;
#else
				static_cast<const ElemWhen*>(node);
#endif

			const XPath* const		theXPath = when->getXPath();
			assert(theXPath != 0);

			const XObjectPtr	test(theXPath->execute(sourceNode, *this, executionContext));
			assert(test.null() == false);

			if(0 != executionContext.getTraceListeners())
			{
				executionContext.fireSelectEvent(
					SelectionEvent(executionContext,
					sourceNode,
					*when,
					Constants::ATTRNAME_TEST,
					*theXPath,
					test));
			}

			if(test->boolean() == true)
			{
				node->executeChildren(executionContext);

				break;
			}
		}
		else
		{
			// xsl:otherwise
			node->executeChildren(executionContext);
		}
    }
}



bool
ElemChoose::childTypeAllowed(int	xslToken) const
{
	bool	fResult = false;
	
	switch(xslToken)
	{
	// char-instructions 
    case Constants::ELEMNAME_WHEN:
    case Constants::ELEMNAME_OTHERWISE:
		fResult = true;
		break;
		
	default:
		break;
	}
	
	return fResult;
}