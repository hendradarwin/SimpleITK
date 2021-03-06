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
#ifndef __sitkScaleTransform_h
#define __sitkScaleTransform_h

#include "sitkCommon.h"
#include "sitkTransform.h"

namespace itk
{
namespace simple
{

class SITKCommon_EXPORT ScaleTransform
  : public Transform
{
public:
  typedef ScaleTransform Self;
  typedef Transform Superclass;

  explicit ScaleTransform(unsigned int dimensions,
                          const std::vector<double> &scales = std::vector<double>(3,1.0) );

  ScaleTransform( const ScaleTransform & );

  explicit ScaleTransform( const Transform & );

  ScaleTransform &operator=( const ScaleTransform & );


  Self &SetScale(const std::vector<double> &params);
  std::vector<double> GetScale( ) const;

/** fixed parameter */
  Self &SetCenter(const std::vector<double> &params);
  std::vector<double> GetCenter( ) const;

  /** additional methods */
  std::vector<double> GetMatrix() const;

protected:

  virtual void SetPimpleTransform( PimpleTransformBase *pimpleTransform );

private:

  using Superclass::AddTransform;

  struct MyVisitor
  {
    itk::TransformBase *transform;
    ScaleTransform *that;
    template< typename TransformType >
    void operator() ( void ) const
      {
        TransformType *t = dynamic_cast<TransformType*>(transform);
        if (t)
          {
          that->InternalInitialization<TransformType>(t);
          }
      }
  };

  void InternalInitialization(itk::TransformBase *transform);

  template <typename TransformType>
    void InternalInitialization(TransformType *transform);


  nsstd::function<void(std::vector<double>)> m_pfSetCenter;
  nsstd::function<std::vector<double>()> m_pfGetCenter;
  nsstd::function<void(std::vector<double>)> m_pfSetScale;
  nsstd::function<std::vector<double>()> m_pfGetScale;
  nsstd::function<std::vector<double>()> m_pfGetMatrix;


};

}
}

#endif // __sitkScaleTransform_h
