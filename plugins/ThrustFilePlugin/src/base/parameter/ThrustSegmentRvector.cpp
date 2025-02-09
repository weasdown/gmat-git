//$Id$
//------------------------------------------------------------------------------
//                                ThrustSegmentRvector
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
// Author: Peter Candell
// Created: 2022/09/07
//
/**
 * Implements ThrustSegmentRvector class which provides base class for time realated String
 * Parameters
 */
 //------------------------------------------------------------------------------

#include "ThrustSegmentRvector.hpp"
#include "ParameterException.hpp"
#include "StringUtil.hpp"               // for ParseParameter()
#include "MessageInterface.hpp"
#include "RvectorVar.hpp"

//#define DEBUG_TIME_STRING_ADD
//#define DEBUG_TIME_STRING

//---------------------------------
// public methods
//---------------------------------

//------------------------------------------------------------------------------
// ThrustSegmentRvector(const std::string &name, const std::string &typeStr, ...)
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
ThrustSegmentRvector::ThrustSegmentRvector(const std::string &name, const std::string &typeStr,
   GmatBase *obj, const std::string &desc, const std::string &unit,
   bool isSettable, Integer size)
   : RvectorVar(name, typeStr, GmatParam::SYSTEM_PARAM, obj, desc, unit,
      GmatParam::NO_DEP, Gmat::THRUST_SEGMENT, false, isSettable, Gmat::THRUST_SEGMENT, size),
   ThrustSegmentData(name)
{
   std::string type, ownerName, depObj;
   GmatStringUtil::ParseParameter(name, type, ownerName, depObj);
   mOwnerName = ownerName;
   mExpr = name;
   AddRefObject(obj);
}


//------------------------------------------------------------------------------
// ThrustSegmentRvector(const ThrustSegmentRvector &copy)
//------------------------------------------------------------------------------
/**
 * Copy constructor.
 *
 * @param <copy> the parameter to make copy of
 */
 //------------------------------------------------------------------------------
ThrustSegmentRvector::ThrustSegmentRvector(const ThrustSegmentRvector &copy)
   : RvectorVar(copy), ThrustSegmentData(copy)
{
}


//------------------------------------------------------------------------------
// ThrustSegmentRvector& operator=(const ThrustSegmentRvector &right)
//------------------------------------------------------------------------------
/**
 * Assignment operator.
 *
 * @param <right> the parameter to make copy of
 */
 //------------------------------------------------------------------------------
ThrustSegmentRvector& ThrustSegmentRvector::operator=(const ThrustSegmentRvector &right)
{
   if (this != &right)
   {
      RvectorVar::operator=(right);
      ThrustSegmentData::operator=(right);
   }

   return *this;
}


//------------------------------------------------------------------------------
// ~ThrustSegmentRvector()
//------------------------------------------------------------------------------
/**
 * Destructor.
 */
 //------------------------------------------------------------------------------
ThrustSegmentRvector::~ThrustSegmentRvector()
{
}


//-------------------------------------
// Inherited methods from Parameter
//-------------------------------------

//------------------------------------------------------------------------------
// const virtual Rvector3& EvaluateRvector3()
//------------------------------------------------------------------------------
/**
 * @return newly evaluated value of parameter
 */
 //------------------------------------------------------------------------------
const Rvector& ThrustSegmentRvector::EvaluateRvector()
{
   Evaluate();
   return mRvectorValue;
}

//------------------------------------------------------------------------------
// bool IsOptionalField(const std::string &field) const
//------------------------------------------------------------------------------
/**
 * @return true if input field name is optional field, false otherwise
 */
 //------------------------------------------------------------------------------
bool ThrustSegmentRvector::IsOptionalField(const std::string &field) const
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
Integer ThrustSegmentRvector::GetNumRefObjects() const
{
   return ThrustSegmentData::GetNumRefObjects();
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
bool ThrustSegmentRvector::AddRefObject(GmatBase *obj, bool replaceName)
{
#ifdef DEBUG_TIME_STRING_ADD
   MessageInterface::ShowMessage("In ThrustSegmentRvector::AddRefObject - obj is %s\n",
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
      return ThrustSegmentData::AddRefObject(obj->GetType(), obj->GetName(), obj,
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
bool ThrustSegmentRvector::Validate()
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
bool ThrustSegmentRvector::Initialize()
{
   try
   {
      InitializeRefObjects();
   }
   catch (BaseException &e)
   {
#if DEBUG_ThrustSegmentRvector
      MessageInterface::ShowMessage
      ("ThrustSegmentRvector::Initialize() Fail to initialize Parameter '%s'\n",
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
bool ThrustSegmentRvector::RenameRefObject(const UnsignedInt type,
   const std::string &oldName,
   const std::string &newName)
{
   return ThrustSegmentData::RenameRefObject(type, oldName, newName);
}


//------------------------------------------------------------------------------
// virtual std::string GetRefObjectName(const UnsignedInt type) const
//------------------------------------------------------------------------------
/**
 * Calls ThrustSegmentData to get reference object name for given type.
 *
 * @return reference object name.
 */
 //------------------------------------------------------------------------------
std::string ThrustSegmentRvector::GetRefObjectName(const UnsignedInt type) const
{
   return ThrustSegmentData::GetRefObjectName(type);
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
const StringArray& ThrustSegmentRvector::GetRefObjectNameArray(const UnsignedInt type)
{
   return ThrustSegmentData::GetRefObjectNameArray(type);
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
bool ThrustSegmentRvector::SetRefObjectName(const UnsignedInt type,
   const std::string &name)
{
   return ThrustSegmentData::SetRefObjectName(type, name);
}


//------------------------------------------------------------------------------
// virtual GmatBase* GetRefObject(const UnsignedInt type,
//                                const std::string &name)
//------------------------------------------------------------------------------
/**
 * Calls ThrustSegmentData to get object pointer of given type and name
 *
 * @param <type> object type
 * @param <name> object name
 *
 * @return reference object pointer for given object type and name
 */
 //------------------------------------------------------------------------------
GmatBase* ThrustSegmentRvector::GetRefObject(const UnsignedInt type,
   const std::string &name)
{
   return ThrustSegmentData::GetRefObject(type, name);
}


//------------------------------------------------------------------------------
// virtual bool SetRefObject(GmatBase *obj, const UnsignedInt type,
//                           const std::string &name = "")
//------------------------------------------------------------------------------
/**
 * Calls ThrustSegmentData to set reference object pointer to given type and name.
 *
 * @param <obj>  reference object pointer
 * @param <type> object type
 * @param <name> object name
 *
 * @return true if object pointer is successfully set.
 *
 */
 //------------------------------------------------------------------------------
bool ThrustSegmentRvector::SetRefObject(GmatBase *obj, const UnsignedInt type,
   const std::string &name)
{
#if DEBUG_REF_OBJECT
   MessageInterface::ShowMessage
   ("ThrustSegmentRvector::SetRefObject() <%p>'%s' entered, obj=<%p><%s>'%s', type=%d, name='%s'\n",
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

   bool setOk = ThrustSegmentData::SetRefObject(obj, type, name);

#if DEBUG_REF_OBJECT
   MessageInterface::ShowMessage
   ("ThrustSegmentRvector::SetRefObject() <%p>'%s' returning %d\n", this,
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
const std::string& ThrustSegmentRvector::GetGeneratingString(Gmat::WriteMode mode,
   const std::string &prefix,
   const std::string &useName)
{
#ifdef DEBUG_GEN_STRING
   MessageInterface::ShowMessage
   ("ThrustSegmentRvector::GetGeneratingString() this=<%p>'%s' entered, mode=%d, prefix='%s', "
      "useName='%s'\n", this, GetName().c_str(), mode, prefix.c_str(), useName.c_str());
   MessageInterface::ShowMessage
   ("   mExpr='%s', mDepObjectName='%s'\n", mExpr.c_str(), mDepObjectName.c_str());
#endif

   // We want to skip RvectorVar::GetGeneratingString() since it is handled specially
   // for String
   return Parameter::GetGeneratingString(mode, prefix, useName);
}

