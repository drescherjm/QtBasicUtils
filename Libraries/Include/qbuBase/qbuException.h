/*=========================================================================

Copyright (c) Insight Software Consortium. All rights reserved.
See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

Portions of this code are covered under the VTK copyright.
See VTKCopyright.txt or http://www.kitware.com/VTKCopyright.htm for details.

This software is distributed WITHOUT ANY WARRANTY; without even 
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#pragma once

#ifndef QBUEXCEPTION_H
#define QBUEXCEPTION_H

#include <stdexcept>
#include <QSharedDataPointer>

class QTextStream;

/////////////////////////////////////////////////////////////////////////////////////////


/**	
*	\brief This class will serve the base of all exceptions thrown within the project
*	\ingroup smBase
*/
class qbuException : public std::exception
{
public:
	typedef std::exception Superclass;
	/** Various types of constructors.  Note that these functions will be
	* called when children are instantiated.  The default constructor and
	* the copy constructor of smException never throw an exception. */
	qbuException();
	explicit qbuException(const char *file, unsigned int lineNumber=0,
		const char *desc="None", const char *loc="Unknown");
	explicit qbuException(const std::string& file, unsigned int lineNumber=0,
		const std::string& desc="None",
		const std::string& loc="Unknown");
	qbuException( const qbuException &orig );

	/** Virtual destructor needed for subclasses. Has to have empty throw(). */
	virtual ~qbuException() throw();

	/** Assignment operator. */
	qbuException &operator= ( const qbuException &orig );

	/** Equivalence operator. */
	virtual bool operator==( const qbuException &orig );

	virtual const char *GetNameOfClass() const 
	{return "smException";}

	/** Print exception information.  This method can be overridden by
	* specific exception subtypes.  The default is to print out the
	* location where the exception was first thrown and any description
	* provided by the ``thrower''.   */
	virtual void Print(std::ostream& os) const;

	virtual void Print(QTextStream& os) const;

	/** Methods to get and set the Location and Description fields. The Set
	* methods are overloaded to support both std::string and const char 
	* array types. Get methods return const char arrays. */
	virtual void SetLocation(const std::string& s);
	virtual void SetDescription(const std::string& s);
	virtual void SetLocation(const char * s);
	virtual void SetDescription (const char *s);
	virtual const char *GetLocation()    const;
	virtual const char *GetDescription() const;

	/** What file did the exception occur in? */
	virtual const char *GetFile()    const;

	/** What line did the exception occur in? */
	virtual unsigned int GetLine() const;

	/** Provide std::exception::what() implementation. */
	virtual const char* what() const throw();
private:
	class		qbuPrivate;
	QSharedDataPointer<qbuPrivate> m_pPrivate;
	const qbuPrivate * GetExceptionData() const;
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif // QBUEXCEPTION_H
