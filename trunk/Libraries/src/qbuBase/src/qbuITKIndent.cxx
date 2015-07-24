/*=========================================================================

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

  Portions of this code are covered under the VTK copyright.
  See VTKCopyright.txt or http://www.kitware.com/VTKCopyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include "qbuBasePCH.h"
#include "qbuBase/qbuITKIndent.h"

#define ITK_STD_INDENT 2
#define ITK_NUMBER_OF_BLANKS 40

static const char blanks[ITK_NUMBER_OF_BLANKS+1] =
"                                        ";

/**
 * Instance creation.
 */
qbuITKIndent*
qbuITKIndent::
New()
{
  return new Self;
}
  
/////////////////////////////////////////////////////////////////////////////////////////
/**
 * Determine the next indentation level. Keep indenting by two until the 
 * max of forty.
 */
qbuITKIndent 
qbuITKIndent
::GetNextIndent()
{
  int indent = m_Indent + ITK_STD_INDENT;
  if ( indent > ITK_NUMBER_OF_BLANKS )
    {
    indent = ITK_NUMBER_OF_BLANKS;
    }
  return indent;
}

/////////////////////////////////////////////////////////////////////////////////////////

const char* qbuITKIndent::getIndent()
{
	return (blanks + (ITK_NUMBER_OF_BLANKS-m_Indent));
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 * Print out the indentation. Basically output a bunch of spaces.
 */
std::ostream& 
operator<<(std::ostream& os, const qbuITKIndent& ind)
{
  os << blanks + (ITK_NUMBER_OF_BLANKS-ind.m_Indent);
  return os;
}

/////////////////////////////////////////////////////////////////////////////////////////

QTextStream& operator<<(QTextStream& os, const qbuITKIndent& ind)
{
	os << QString(blanks + (ITK_NUMBER_OF_BLANKS - ind.m_Indent));
	return os;
}

/////////////////////////////////////////////////////////////////////////////////////////

