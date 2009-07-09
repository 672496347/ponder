/****************************************************************************
**
** Copyright (C) 2009 TECHNOGERMA Systems France and/or its subsidiary(-ies).
** Contact: Technogerma Systems France Information (contact@technogerma.fr)
**
** This file is part of the CAMP library.
**
** Commercial Usage
** Licensees holding valid CAMP Commercial licenses may use this file in
** accordance with the CAMP Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and TECHNOGERMA Systems France.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL3.txt included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at sales@technogerma.fr.
**
****************************************************************************/


#ifndef CAMP_CLASSVISITOR_HPP
#define CAMP_CLASSVISITOR_HPP


#include <camp/config.hpp>


namespace camp
{
class Property;
class SimpleProperty;
class ArrayProperty;
class EnumProperty;
class UserProperty;
class Function;

/**
 * \brief Base class for writing custom Class visitors
 *
 * A ClassVisitor, when applied to a Class, will be notified for each member property and function of
 * the target class. To receive this notification for a specific type T of property or function,
 * you have to override the \c visit(T) function.
 *
 * The benefit of such visitation is that you directly get the actual type of the
 * property or function, and can handle it safely without having to use dangerous downcasts.
 *
 * Another benefit of this method is that you can easily filter the properties and functions
 * according to their C++ type: if you don't want to handle a specific type of property or function,
 * just don't override the corresponding \c visit function.
 *
 * Here an example of a visitor which prints the contents of a class:
 * \code
 * class MyClassVisitor : public camp::ClassVisitor
 * {
 *     void visit(const camp::SimpleProperty& property)
 *     {
 *         std::cout << "Simple property: " << property.name() << std::endl;
 *     }
 * 
 *     void visit(const camp::ArrayProperty& property)
 *     {
 *         std::cout << "Array property: " << property.name() << " - "
 *                   << "dynamic:" << property.dynamic() << std::endl;
 *     }
 * 
 *     void visit(const camp::EnumProperty& property)
 *     {
 *         std::cout << "Enum property: " << property.name() << " - "
 *                   << "owner enum:" << property.getEnum().name() << std::endl;
 *     }
 * 
 *     void visit(const camp::UserProperty& property)
 *     {
 *         std::cout << "User property: " << property.name() << " - "
 *                   << "owner class:" << property.getClass().name() << std::endl;
 *     }
 * 
 *     void visit(const camp::Function& function)
 *     {
 *         std::cout << "Function: " << function.name() << " - "
 *                   << "number of arguments:" << function.argCount() << std::endl;
 *     }
 * };
 * 
 * const camp::Class& metaclass = camp::classByName("MyClass");
 * MyClassVisitor visitor;
 * metaclass.visit(visitor);
 * \endcode
 */
class CAMP_API ClassVisitor
{
public:

    /**
     * \brief Destructor
     */
    virtual ~ClassVisitor();

    /**
     * \brief Visit any kind of property
     *
     * This function is a generic callback which can be used
     * to receive all property types which are not handled with
     * their derived type.
     *
     * \param property Property which is being visited
     */
    virtual void visit(const Property& property);

    /**
     * \brief Visit a simple property
     *
     * \param property Property which is being visited
     */
    virtual void visit(const SimpleProperty& property);

    /**
     * \brief Visit an array property
     *
     * \param property Property which is being visited
     */
    virtual void visit(const ArrayProperty& property);

    /**
     * \brief Visit an enum property
     *
     * \param property Property which is being visited
     */
    virtual void visit(const EnumProperty& property);

    /**
     * \brief Visit a user property
     *
     * \param property Property which is being visited
     */
    virtual void visit(const UserProperty& property);

    /**
     * \brief Visit a function
     *
     * \param function Function which is being visited
     */
    virtual void visit(const Function& function);

protected:

    /**
     * \brief Default constructor
     */
    ClassVisitor();
};

} // namespace camp


#endif // CAMP_VALUEVISITOR_HPP
