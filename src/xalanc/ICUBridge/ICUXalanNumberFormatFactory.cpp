/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements. See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership. The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the  "License");
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

#include "ICUXalanNumberFormatFactory.hpp"



#include "ICUXalanNumberFormatProxy.hpp"



XALAN_CPP_NAMESPACE_BEGIN



ICUXalanNumberFormatFactory::ICUXalanNumberFormatFactory(MemoryManager& theManager) :
	StylesheetExecutionContextDefault::XalanNumberFormatFactory(),
    m_memoryManager(theManager)
{
}



ICUXalanNumberFormatFactory::~ICUXalanNumberFormatFactory()
{
}



XalanNumberFormat*
ICUXalanNumberFormatFactory::create()
{
    typedef ICUXalanNumberFormatProxy ThisType;

    XalanMemMgrAutoPtr<ThisType, false> theGuard( m_memoryManager , (ThisType*)m_memoryManager.allocate(sizeof(ThisType)));

    ThisType* theResult = theGuard.get();

    new (theResult) ThisType(m_memoryManager);

   theGuard.release();

   return theResult;
}



XALAN_CPP_NAMESPACE_END
