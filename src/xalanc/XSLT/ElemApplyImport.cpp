/*
 * Copyright 1999-2004 The Apache Software Foundation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "ElemApplyImport.hpp"



#include <xercesc/sax/AttributeList.hpp>



#include <xalanc/XalanDOM/XalanDOMException.hpp>



#include <xalanc/PlatformSupport/DOMStringHelper.hpp>
#include <xalanc/PlatformSupport/XalanMessageLoader.hpp>



#include <xalanc/DOMSupport/DOMServices.hpp>



#include "Constants.hpp"
#include "StylesheetConstructionContext.hpp"
#include "StylesheetExecutionContext.hpp"



XALAN_CPP_NAMESPACE_BEGIN



ElemApplyImport::ElemApplyImport(
			StylesheetConstructionContext&	constructionContext,
			Stylesheet&						stylesheetTree,
			const AttributeListType&		atts,
			int								lineNumber, 
			int								columnNumber) :
		ElemTemplateElement(constructionContext,
							stylesheetTree,
							lineNumber,
							columnNumber,
							StylesheetConstructionContext::ELEMNAME_APPLY_IMPORTS)
{
	const unsigned int	nAttrs = atts.getLength();

    for(unsigned int i = 0; i < nAttrs; i++)
    {
		const XalanDOMChar*	const	aname = atts.getName(i);

		if(isAttrOK(aname, atts, i, constructionContext) == false)
		{
            XalanDOMString  theResult(constructionContext.getMemoryManager());

			constructionContext.error(
					XalanMessageLoader::getMessage(
						XalanMessages::TemplateHasIllegalAttribute_2Param,
                            theResult, 
							Constants::ELEMNAME_APPLY_IMPORTS_WITH_PREFIX_STRING.c_str(),
							aname),
					0,
					this);
		}
    }
}



const XalanDOMString&
ElemApplyImport::getElementName() const
{
	return Constants::ELEMNAME_APPLY_IMPORTS_WITH_PREFIX_STRING;
}



#if !defined(XALAN_RECURSIVE_STYLESHEET_EXECUTION)
const ElemTemplateElement*
ElemApplyImport::startElement(StylesheetExecutionContext&	executionContext) const
{
	if (executionContext.getCurrentTemplate() == 0)
	{
        XalanDOMString  theResult(executionContext.getMemoryManager());

		executionContext.error(XalanMessageLoader::getMessage(XalanMessages::NoCurrentTemplate, theResult),
				executionContext.getCurrentNode(), getLocator());
	}

	ElemTemplateElement::startElement(executionContext);

	executionContext.pushInvoker(this);

	executionContext.pushContextMarker();
	
	return findTemplateToTransformChild(	
			executionContext,
			*this,
			0,
			executionContext.getCurrentNode());
}



void
ElemApplyImport::endElement(StylesheetExecutionContext&		executionContext) const
{
	executionContext.popContextMarker();

	executionContext.popInvoker();

	ElemTemplateElement::endElement(executionContext);
}



const ElemTemplateElement*
ElemApplyImport::getNextChildElemToExecute(
		StylesheetExecutionContext&		/* execution Context */,
		const ElemTemplateElement*		/* currentElem */) const
{
	return 0;
}
#endif



#if defined(XALAN_RECURSIVE_STYLESHEET_EXECUTION)
void
ElemApplyImport::execute(StylesheetExecutionContext&	executionContext) const
{
	XalanNode* const	sourceNode = executionContext.getCurrentNode();
	assert(sourceNode != 0);

	if (executionContext.getCurrentTemplate() == 0)
	{
		executionContext.error(XalanMessageLoader::getMessage(XalanMessages::NoCurrentTemplate),
				sourceNode, getLocator());
	}

	ElemTemplateElement::execute(executionContext);

	const StylesheetExecutionContext::PushAndPopContextMarker	thePushPop(executionContext);

	transformChild(
			executionContext,
			*this,
			0,
			sourceNode);
}
#endif



ElemTemplateElement*
ElemApplyImport::appendChildElem(ElemTemplateElement*	/* newChild */)
{
	throw XalanDOMException(XalanDOMException::HIERARCHY_REQUEST_ERR);

	return 0;
}



XALAN_CPP_NAMESPACE_END
