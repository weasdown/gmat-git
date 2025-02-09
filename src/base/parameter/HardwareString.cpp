//$Id$
//------------------------------------------------------------------------------
//                                HardwareString
//------------------------------------------------------------------------------
// GMAT: General Mission Analysis Tool
//
// Copyright (c) 2002 - 2022 United States Government as represented by the
// Administrator of the National Aeronautics and Space Administration.
// All Other Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License"); 
// You may not use this file except in compliance with the License. 
// You may obtain a copy of the License at:
// http://www.apache.org/licenses/LICENSE-2.0. 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either 
// express or implied.   See the License for the specific language
// governing permissions and limitations under the License.
//
// Developed jointly by NASA/GSFC and Thinking Systems, Inc. under contract
// number S-67573-G
//
// Author: Linda Jun
// Created: 2006/03/09
//
/**
 * Implements HardwareString class which provides base class for time realated String
 * Parameters
 */
 //------------------------------------------------------------------------------

#include "HardwareString.hpp"
#include "ParameterException.hpp"
#include "StringUtil.hpp"               // for ParseParameter()
#include "MessageInterface.hpp"

//#define DEBUG_TIME_STRING_ADD
//#define DEBUG_TIME_STRING

//---------------------------------
// public methods
//---------------------------------

//------------------------------------------------------------------------------
// HardwareString(const std::string &name, const std::string &typeStr, ...)
//------------------------------------------------------------------------------
/**
 * Constructor.
 *
 * @param <name> name of the parameter
 * @param <typeStr> type of the parameter
 * @param <obj> reference object pointer
 * @param <desc> description of the parameter
 * @param <unit> unit of the parameter
 * @param <isSettable> true if parameter is settable
 */
 //------------------------------------------------------------------------------
HardwareString::HardwareString(const std::string &name, const std::string &typeStr,
   UnsignedInt ownerType, UnsignedInt ownedObjType,
   GmatBase *obj, const std::string &desc, const std::string &unit,
   bool isSettable)
   : StringVar(name, typeStr, GmatParam::SYSTEM_PARAM, obj, desc, unit,
      GmatParam::ATTACHED_OBJ, ownerType, false, isSettable, ownedObjType),
   SpacecraftData(name)
{
   std::string type, ownerName, depObj;
   GmatStringUtil::ParseParameter(name, type, ownerName, depObj);
   mOwnerName = ownerName;
   mExpr = name;
   AddRefObject(obj);
}


//------------------------------------------------------------------------------
// HardwareString(const HardwareString &copy)
//------------------------------------------------------------------------------
/**
 * Copy constructor.
 *
 * @param <copy> the parameter to make copy of
 */
 //------------------------------------------------------------------------------
HardwareString::HardwareString(const HardwareString &copy)
   : StringVar(copy), SpacecraftData(copy)
{
}


//------------------------------------------------------------------------------
// HardwareString& operator=(const HardwareString &right)
//------------------------------------------------------------------------------
/**
 * Assignment operator.
 *
 * @param <right> the parameter to make copy of
 */
 //------------------------------------------------------------------------------
HardwareString& HardwareString::operator=(const HardwareString &right)
{
   if (this != &right)
   {
      StringVar::operator=(right);
      SpacecraftData::operator=(right);
   }

   return *this;
}


//------------------------------------------------------------------------------
// ~HardwareString()
//------------------------------------------------------------------------------
/**
 * Destructor.
 */
 //------------------------------------------------------------------------------
HardwareString::~HardwareString()
{
}


//-------------------------------------
// Inherited methods from Parameter
//-------------------------------------

//------------------------------------------------------------------------------
// const virtual std::string& EvaluateString()
//------------------------------------------------------------------------------
/**
 * @return newly evaluated value of parameter
 */
 //------------------------------------------------------------------------------
const std::string& HardwareString::EvaluateString()
{
   Evaluate();
   return mStringValue;
}

//------------------------------------------------------------------------------
// bool IsOptionalField(const std::string &field) const
//------------------------------------------------------------------------------
/**
 * @return true if input field name is optional field, false otherwise
 */
 //------------------------------------------------------------------------------
bool HardwareString::IsOptionalField(const std::string &field) const
{
   return false;
}

//------------------------------------------------------------------------------
// virtual Integer GetNumRefObjects() const
//------------------------------------------------------------------------------
/**
 * @return number of reference objects set.
 */
 //------------------------------------------------------------------------------
Integer HardwareString::GetNumRefObjects() const
{
   return SpacecraftData::GetNumRefObjects();
}


//------------------------------------------------------------------------------
// virtual bool (GmatBase *obj, bool replaceName = false)
//------------------------------------------------------------------------------
/**
 * Adds reference object.
 *
 * @param <obj> object pointer
 *
 * @return true if the object has been added.
 */
 //------------------------------------------------------------------------------
bool HardwareString::AddRefObject(GmatBase *obj, bool replaceName)
{
#ifdef DEBUG_TIME_STRING_ADD
   MessageInterface::ShowMessage("In HardwareString::AddRefObject - obj is %s\n",
      (obj ? " NOT NULL" : "NULL!"));
   MessageInterface::ShowMessage("... replaceName = %s\n",
      (replaceName ? "true" : "false"));
   if (obj)
   {
      MessageInterface::ShowMessage("... obj is %s\n", obj->GetName().c_str());
      MessageInterface::ShowMessage("... type is %d\n", obj->GetType());
   }
#endif

   if (obj != NULL)
      return SpacecraftData::AddRefObject(obj->GetType(), obj->GetName(), obj,
         replaceName);
   else
      return false;
}


//------------------------------------------------------------------------------
// virtual bool Validate()
//------------------------------------------------------------------------------
/**
 * Validates reference objects.
 *
 * @return true if all objects are set; false otherwise
 */
 //------------------------------------------------------------------------------
bool HardwareString::Validate()
{
   return ValidateRefObjects(this);
}


//------------------------------------------------------------------------------
// virtual bool Initialize()
//------------------------------------------------------------------------------
/**
 * Initializes reference objects.
 *
 * @return true if all objects are set; false otherwise
 */
 //------------------------------------------------------------------------------
bool HardwareString::Initialize()
{
   try
   {
      InitializeRefObjects();
   }
   catch (BaseException &e)
   {
#if DEBUG_HardwareString
      MessageInterface::ShowMessage
      ("HardwareString::Initialize() Fail to initialize Parameter '%s'\n",
         this->GetName().c_str());
#endif

      throw ParameterException
      ("WARNING:  " + e.GetFullMessage() + " in " + GetName() + "\n");
   }

   return true;
}


//-------------------------------------
// Methods inherited from GmatBase
//-------------------------------------

//---------------------------------------------------------------------------
//  bool RenameRefObject(const UnsignedInt type,
//                       const std::string &oldName, const std::string &newName)
//---------------------------------------------------------------------------
bool HardwareString::RenameRefObject(const UnsignedInt type,
   const std::string &oldName,
   const std::string &newName)
{
   return SpacecraftData::RenameRefObject(type, oldName, newName);
}


//------------------------------------------------------------------------------
// virtual std::string GetRefObjectName(const UnsignedInt type) const
//------------------------------------------------------------------------------
/**
 * Calls SpacecraftData to get reference object name for given type.
 *
 * @return reference object name.
 */
 //------------------------------------------------------------------------------
std::string HardwareString::GetRefObjectName(const UnsignedInt type) const
{
   return SpacecraftData::GetRefObjectName(type);
}


//------------------------------------------------------------------------------
// virtual const StringArray& GetRefObjectNameArray(const UnsignedInt type)
//------------------------------------------------------------------------------
/**
 * Retrieves reference object name array for given type. It will return all
 * object names if type is Gmat::UNKNOWN_NAME.
 *
 * @param <type> object type
 * @return reference object name.
 */
 //------------------------------------------------------------------------------
const StringArray& HardwareString::GetRefObjectNameArray(const UnsignedInt type)
{
   return SpacecraftData::GetRefObjectNameArray(type);
}


//------------------------------------------------------------------------------
// virtual bool SetRefObjectName(const UnsignedInt type,
//                               const std::string &name)
//------------------------------------------------------------------------------
/**
 * Sets reference object name to given object type.
 *
 * @param <type> object type
 * @param <name> object name
 *
 */
 //------------------------------------------------------------------------------
bool HardwareString::SetRefObjectName(const UnsignedInt type,
   const std::string &name)
{
   return SpacecraftData::SetRefObjectName(type, name);
}


//------------------------------------------------------------------------------
// virtual GmatBase* GetRefObject(const UnsignedInt type,
//                                const std::string &name)
//------------------------------------------------------------------------------
/**
 * Calls SpacecraftData to get object pointer of given type and name
 *
 * @param <type> object type
 * @param <name> object name
 *
 * @return reference object pointer for given object type and name
 */
 //------------------------------------------------------------------------------
GmatBase* HardwareString::GetRefObject(const UnsignedInt type,
   const std::string &name)
{
   return SpacecraftData::GetRefObject(type, name);
}


//------------------------------------------------------------------------------
// virtual bool SetRefObject(GmatBase *obj, const UnsignedInt type,
//                           const std::string &name = "")
//------------------------------------------------------------------------------
/**
 * Calls SpacecraftData to set reference object pointer to given type and name.
 *
 * @param <obj>  reference object pointer
 * @param <type> object type
 * @param <name> object name
 *
 * @return true if object pointer is successfully set.
 *
 */
 //------------------------------------------------------------------------------
bool HardwareString::SetRefObject(GmatBase *obj, const UnsignedInt type,
   const std::string &name)
{
#if DEBUG_REF_OBJECT
   MessageInterface::ShowMessage
   ("HardwareString::SetRefObject() <%p>'%s' entered, obj=<%p><%s>'%s', type=%d, name='%s'\n",
      this, this->GetName().c_str(), obj, obj ? obj->GetTypeName().c_str() : "NULL",
      obj ? obj->GetName().c_str() : "NULL", type, name.c_str());
#endif

   if (obj == NULL)
      return false;

#if DEBUG_REF_OBJECT
   MessageInterface::ShowMessage
   ("   Is%sGlobal=%d, Is%sLocal=%d\n", name.c_str(), obj->IsGlobal(),
      name.c_str(), obj->IsLocal());
#endif

   if (obj->GetName() == mParamOwnerName)
      SetOwner(obj);

   bool setOk = SpacecraftData::SetRefObject(obj, type, name);

#if DEBUG_REF_OBJECT
   MessageInterface::ShowMessage
   ("HardwareString::SetRefObject() <%p>'%s' returning %d\n", this,
      this->GetName().c_str(), setOk);
#endif

   return setOk;
}


//------------------------------------------------------------------------------
// const std::string& GetGeneratingString(...)
//------------------------------------------------------------------------------
/**
 * @see GmatBase
 */
 //------------------------------------------------------------------------------
const std::string& HardwareString::GetGeneratingString(Gmat::WriteMode mode,
   const std::string &prefix,
   const std::string &useName)
{
#ifdef DEBUG_GEN_STRING
   MessageInterface::ShowMessage
   ("HardwareString::GetGeneratingString() this=<%p>'%s' entered, mode=%d, prefix='%s', "
      "useName='%s'\n", this, GetName().c_str(), mode, prefix.c_str(), useName.c_str());
   MessageInterface::ShowMessage
   ("   mExpr='%s', mDepObjectName='%s'\n", mExpr.c_str(), mDepObjectName.c_str());
#endif

   // We want to skip StringVar::GetGeneratingString() since it is handled specially
   // for String
   return Parameter::GetGeneratingString(mode, prefix, useName);
}

