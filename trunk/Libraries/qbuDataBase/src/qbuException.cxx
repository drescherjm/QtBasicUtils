/*=========================================================================

Copyright (c) Insight Software Consortium. All rights reserved.
See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

Portions of this code are covered under the VTK copyright.
See VTKCopyright.txt or http://www.kitware.com/VTKCopyright.htm for details.

This software is distributed WITHOUT ANY WARRANTY; without even 
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include "smBasePCH.h"
#include "smException.h"
#include <sstream>
#include <QSharedData>
#include "smitkIndent.h"

/////////////////////////////////////////////////////////////////////////////////////////

class smException::smPrivate : public QSharedData
{
protected:
	// Constructor. Might throw an exception.
	smPrivate(
		const std::string& file, unsigned int line,
		const std::string& description,
		const std::string& location)
		:
	m_Location(location),
		m_Description(description),
		m_File(file),
		m_Line(line)
	{
		std::stringstream loc;
		loc << ":" << m_Line << ":\n";
		m_What = m_File;
		m_What += loc.str();
		m_What += m_Description;
		m_WhatPointer = m_What.c_str();
	}

private:
	void operator=(const smPrivate&); //purposely not implemented

	friend class smException;

	// The data members should never change after construction of the ExceptionData object,
	// to ensure the consistency of the exception data.
	const std::string       m_Location;
	const std::string       m_Description;
	const std::string       m_File;
	const unsigned int      m_Line;
	std::string             m_What;
	const char *            m_WhatPointer;
};

/////////////////////////////////////////////////////////////////////////////////////////

smException::smException()
{
	// The default construction never throws an exception.
}

smException::smException(
								 const char *file,
								 unsigned int lineNumber,
								 const char *desc,
								 const char *loc)
{
	m_pPrivate = new smPrivate(file == 0 ? "" : file, lineNumber, desc == 0 ? "" : desc, loc == 0 ? "" : loc);
}

smException::smException(
								 const std::string& file,
								 unsigned int lineNumber,
								 const std::string& desc,
								 const std::string& loc)
{
	m_pPrivate = new smPrivate(file, lineNumber, desc, loc);
}

smException::smException( const smException &orig )
:
Superclass(orig),
m_pPrivate(orig.m_pPrivate)
{
	// This copy construction never throws, because it just copies the smart pointer.
}


smException::~smException() throw()
{
	// During destruction, the reference count of the ReferenceCountedExceptionData will be decreased
	// automatically, by the destructor of the smart pointer.
}

const smException::smPrivate *
smException::GetExceptionData() const
{
	// Note: dynamic_cast does a runtime check if the m_ExceptionData pointer is indeed
	// pointing to an ExceptionData object. In this case, a static_cast could have been
	// used instead, which only does compile time checking. But we expect the
	// runtime overhead of this particular dynamic_cast to be insignificant.
	const smPrivate * thisData = 
		dynamic_cast< const smPrivate *>( this->m_pPrivate.data() );
	return thisData;
}

smException &
smException::operator= ( const smException &orig )
{
	// Note: there is no superclass assignment here, because std::exception::operator= 
	// appears have a bug on some platforms, including MSVC 2003. As reported by Jouni Kiviniemi:
	// https://connect.microsoft.com/VisualStudio/feedback/ViewFeedback.aspx?FeedbackID=328570

	// Assigns its smart pointer:
	m_pPrivate = orig.m_pPrivate;
	return *this;
}

bool
smException::operator==( const smException &orig )
{
	// operator== is reimplemented, but it still behaves like the previous version, from ITK 3.6.0.
	const smPrivate *const thisData = this->GetExceptionData();
	const smPrivate *const origData = orig.GetExceptionData();

	if ( thisData == origData )
	{
		return true;
	}
	else
	{
		return (thisData != 0) && (origData != 0) &&
			thisData->m_Location == origData->m_Location &&
			thisData->m_Description == origData->m_Description &&
			thisData->m_File == origData->m_File &&
			thisData->m_Line == origData->m_Line; 
	}
}

void
smException::SetLocation(const std::string& s)
{
	const bool IsNull = !m_pPrivate;
	m_pPrivate = new smPrivate(
		IsNull ? "" : this->GetExceptionData()->m_File.c_str(),
		IsNull ? 0 : this->GetExceptionData()->m_Line,
		IsNull ? "" : this->GetExceptionData()->m_Description.c_str(),
		s);
}

void
smException::SetDescription(const std::string& s) 
{
	const bool IsNull =  !m_pPrivate;
	m_pPrivate = new smPrivate(
		IsNull ? "" : this->GetExceptionData()->m_File.c_str(),
		IsNull ? 0 : this->GetExceptionData()->m_Line,
		s,
		IsNull ? "" : this->GetExceptionData()->m_Location.c_str());
}

void
smException::SetLocation(const char * s)
{
	std::string location;
	if( s ) 
	{
		location = s;
	}
	smException::SetLocation( location );
}

void
smException::SetDescription(const char *s)
{
	std::string description;
	if( s ) 
	{
		description = s;
	}
	smException::SetDescription( description );
}

const char *
smException::GetLocation() const 
{
	// Note: std::string::c_str() might throw an exception.
	return !m_pPrivate ? "" : this->GetExceptionData()->m_Location.c_str();
}

const char *
smException::GetDescription() const
{
	// Note: std::string::c_str() might throw an exception.
	return !m_pPrivate ? "" : this->GetExceptionData()->m_Description.c_str();
}

const char *
smException::GetFile() const 
{
	// Note: std::string::c_str() might throw an exception.
	return !m_pPrivate ? "" : this->GetExceptionData()->m_File.c_str();
}

unsigned int
smException::GetLine() const 
{
	return !m_pPrivate ? 0 : this->GetExceptionData()->m_Line;
}

const char *
smException::what() const throw()
{ 
	const smPrivate * const thisData = this->GetExceptionData();

	// Note: m_What.c_str() wouldn't be safe, because c_str() might throw an exception.
	return thisData ? thisData->m_WhatPointer : "smException";
}

void
smException
::Print(std::ostream& os) const
{
	smitkIndent indent;

	// Print header
	os << std::endl;
	os << indent << this->GetNameOfClass() << " (" << this << ")\n";

	// Print self
	indent.GetNextIndent();

	if (m_pPrivate)
	{
		const smPrivate & data = *(this->GetExceptionData());

		if (! data.m_Location.empty()) 
		{
			os << indent << "Location: \"" << data.m_Location << "\" " << std::endl;
		}

		if (! data.m_File.empty()) 
		{
			os << indent << "File: " << data.m_File << std::endl;
			os << indent << "Line: " << data.m_Line << std::endl;
		}

		if (! data.m_Description.empty()) 
		{
			os << indent << "Description: " << data.m_Description << std::endl;  
		}
	}
	// Print trailer
	os << indent << std::endl;
}  
