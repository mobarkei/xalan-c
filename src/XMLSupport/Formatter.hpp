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
#if !defined(FORMATTER_HEADER_GUARD_1357924680)
#define FORMATTER_HEADER_GUARD_1357924680



// Base include file.  Must be first.
#include <XMLSupport/XMLSupportDefinitions.hpp>



class DOM_Document;
class DOMString;
class FormatterListener;
class PrintWriter;



class XALAN_XMLSUPPORT_EXPORT Formatter
{
public:

#if defined(XALAN_INLINE_INITIALIZATION)

	/**
	 * Output results as XML.
	 */
	const int OUTPUT_METH_XML = 1;
  
	/**
	 * Output results as HTML.
	 */
	const int OUTPUT_METH_HTML = 2;
  
	/**
	 * Output results as TEXT.
	 */
	const int OUTPUT_METH_TEXT = 3;
  
#else

	enum eFormats
	{
		OUTPUT_METH_XML = 1,
		OUTPUT_METH_HTML = 2,
		OUTPUT_METH_TEXT = 3
	};

#endif

	Formatter();

	virtual
	~Formatter();

  /**
   * Print the result tree.
	*
   * @param doc      result tree
   * @param pw       printWriter to print the contents to
   * @param resultns value of the result namespace attribute
   * @param format   true if it should be pretty-printed
   */
	virtual void
	toMarkup(
			const DOM_Document&		doc,
			PrintWriter&			pw,
			const DOMString&		resultns,
			bool					format) = 0;

  /**
	* Get the instance of the formatter listener that is associated with this
	* formatter.
	*
   * @return pointer to listener
   */
	virtual FormatterListener*
	getFormatterListener() const = 0;

  /**
	* Set the instance of the formatter listener that is associated with this
	* formatter.
	*
   * @param pw       printWriter to print the contents to
   * @param resultns value of the result namespace attribute
   * @param format   true if it should be pretty-printed
   */
	virtual void
	setFormatterListener(
			PrintWriter&		pw,
			const DOMString&	resultns,
			bool				format) = 0;

  /**
	* Set the instance of the formatter listener that is associated with this
	* formatter.
	*
   * @param pw       printWriter to print the contents to
   * @param resultns value of the result namespace attribute
   * @param format   true if it should be pretty-printed
   * @param fl       pointer to listener to use
   */
	virtual void
	setFormatterListener(FormatterListener*		fl) = 0;
};


#endif	// FORMATTER_HEADER_GUARD_1357924680
