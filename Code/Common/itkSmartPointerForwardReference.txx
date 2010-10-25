/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef __itkSmartPointerForwardReference_txx
#define __itkSmartPointerForwardReference_txx

#include "itkSmartPointerForwardReference.h"

namespace itk
{
//----------------------------------------------------------------------------
template< class T >
SmartPointerForwardReference< T >
::SmartPointerForwardReference (const SmartPointerForwardReference< T > & p)
{
  m_Pointer = p.m_Pointer;
  this->Register();
}

//----------------------------------------------------------------------------
template< class T >
SmartPointerForwardReference< T >
::SmartPointerForwardReference (const WeakPointer< T > & p)
{
  m_Pointer = p.GetPointer();
  this->Register();
}

//----------------------------------------------------------------------------
template< class T >
SmartPointerForwardReference< T >
::SmartPointerForwardReference (T *p)
{
  m_Pointer = p;
  this->Register();
}

//----------------------------------------------------------------------------
template< class T >
SmartPointerForwardReference< T >
::~SmartPointerForwardReference ()
{
  this->UnRegister();
}

//----------------------------------------------------------------------------
template< class T >
T *
SmartPointerForwardReference< T >
::operator->() const
{
  return m_Pointer;
}

//----------------------------------------------------------------------------
template< class T >
SmartPointerForwardReference< T >
::operator T *() const
{
  return m_Pointer;
}

//----------------------------------------------------------------------------
template< class T >
T *
SmartPointerForwardReference< T >
::GetPointer() const
{
  return m_Pointer;
}

//----------------------------------------------------------------------------
template< class T >
bool
SmartPointerForwardReference< T >
::operator<(const SmartPointerForwardReference & r)
{
  return (void *)m_Pointer < (void *)r.m_Pointer;
}

//----------------------------------------------------------------------------
template< class T >
bool
SmartPointerForwardReference< T >
::operator>(const SmartPointerForwardReference & r)
{
  return (void *)m_Pointer > (void *)r.m_Pointer;
}

//----------------------------------------------------------------------------
template< class T >
bool
SmartPointerForwardReference< T >
::operator<=(const SmartPointerForwardReference & r)
{
  return (void *)m_Pointer <= (void *)r.m_Pointer;
}

//----------------------------------------------------------------------------
template< class T >
bool
SmartPointerForwardReference< T >
::operator>=(const SmartPointerForwardReference & r)
{
  return (void *)m_Pointer >= (void *)r.m_Pointer;
}

//----------------------------------------------------------------------------
template< class T >
SmartPointerForwardReference< T > &
SmartPointerForwardReference< T >
::operator=(const SmartPointerForwardReference & r)
{
  return this->operator=( r.GetPointer() );
}

//----------------------------------------------------------------------------
template< class T >
SmartPointerForwardReference< T > &
SmartPointerForwardReference< T >
::operator=(const WeakPointer< T > & r)
{
  return this->operator=( r.GetPointer() );
}

//----------------------------------------------------------------------------
template< class T >
SmartPointerForwardReference< T > &
SmartPointerForwardReference< T >
::operator=(T *r)
{
  if ( m_Pointer != r )
    {
    T *tmp = m_Pointer; //avoid recursive unregisters by retaining temporarily
    m_Pointer = r;
    this->Register();
    if ( tmp )
      {
      tmp->UnRegister();
      }
    }
  return *this;
}

//----------------------------------------------------------------------------
template< class T >
T *
SmartPointerForwardReference< T >
::Print(std::ostream & os) const
{
  // This prints the object pointed to by the pointer
  ( *m_Pointer ).Print(os);
  return m_Pointer;
}

//----------------------------------------------------------------------------
template< class T >
void
SmartPointerForwardReference< T >
::Register()
{
  if ( m_Pointer )
    {
    m_Pointer->Register();
    }
}

//----------------------------------------------------------------------------
template< class T >
void
SmartPointerForwardReference< T >
::UnRegister()
{
  if ( m_Pointer )
    {
    m_Pointer->UnRegister();
    }
}
} //end namespace

#endif
