/*=========================================================================

Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

  Portions of this code are covered under the VTK copyright.
  See VTKCopyright.txt or http://www.kitware.com/VTKCopyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef __QBUITKINDENT_H__
#define __QBUITKINDENT_H__

#include <iostream>

/** \class qbuITKIndent
 * \brief Control indentation during Print() invocation.
 *
 * qbuITKIndent is used to control indentation during the chaining print 
 * process. This way nested objects can correctly indent themselves.
 * This class works with the print methods defined in Object (i.e.,
 * the public method Print() and the protected methods PrintSelf(),
 * PrintHeader(), and PrintTrailer().
 *
 * \ingroup smBase
 */

class qbuITKIndent
{
public:
  /** Standard class typedefs. */
  typedef qbuITKIndent  Self;

  /** Method for creation through the object factory. */
  static Self* New();
  
  /** Destroy this instance. */
  void Delete() {delete this;}

  /** Construct the object with an initial indentation level. */
  qbuITKIndent(int ind=0) {m_Indent=ind;}

  /** Return the name of the class. */
  static const char *GetNameOfClass() {return "qbuITKIndent";}

  /** Determine the next indentation level. Keep indenting by two until the 
   * a maximum of forty spaces is reached.  */
  qbuITKIndent GetNextIndent();

  /** Print out the indentation. Basically output a bunch of spaces.  */
  friend std::ostream& operator<<(std::ostream& os, const qbuITKIndent& o); 

  const char* getIndent();

private:
  int m_Indent;
};


#endif //__QBUITKINDENT_H__