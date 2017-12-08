/*=========================================================================
 *
 *  Copyright Leiden University Medical Center, Erasmus University Medical
 *  Center and contributors
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#ifndef selxDisplacementFieldWarperComponent_h
#define selxDisplacementFieldWarperComponent_h

#include "selxDisplacementFieldMeshWarperComponent.h"

namespace selx {

template< int Dimensionality, class TPixel, class TCoordRepType >
ItkDisplacementFieldMeshWarperComponent< Dimensionality, TPixel, TCoordRepType >
::ItkDisplacementFieldMeshWarperComponent( const std::string & name, LoggerImpl & logger ) : Superclass( name, logger ) {
  this->m_DisplacementFieldTransform = ItkDisplacementFieldTransformType::New();
  this->m_TransformMeshFilter = ItkTransformMeshFilterType::New();
  this->m_TransformMeshFilter->SetTransform( this->m_DisplacementFieldTransform );
};

template< int Dimensionality, class TPixel, class TCoordRepType >
int
ItkDisplacementFieldMeshWarperComponent< Dimensionality, TPixel, TCoordRepType >
::Accept( ItkDisplacementFieldInterfaceType * itkDisplacementFieldInterface )
{
  auto displacementField = itkDisplacementFieldInterface->GetItkDisplacementField();
  this->m_DisplacementFieldTransform->SetDisplacementField( displacementField );

  return 0;
}

template< int Dimensionality, class TPixel, class TCoordRepType >
int
ItkDisplacementFieldMeshWarperComponent< Dimensionality, TPixel, TCoordRepType >
::Accept( ItkMeshInterfaceType * itkMeshInterface )
{
  this->m_TransformMeshFilter->SetInput( itkMeshInterface->GetItkMesh() );

  return 0;
}

template< int Dimensionality, class TPixel, class TCoordRepType >
ItkDisplacementFieldMeshWarperComponent< Dimensionality, TPixel, TCoordRepType >::ItkMeshType *
GetWarpedItkMesh< Dimensionality, TPixel, TCoordRepType >
::Accept( ItkMeshInterfaceType * itkMeshInterface )
{
  this->m_TransformMeshFilter->Update();
  return itkDynamicCastInDebugMode< ItkMeshType * >(this->m_TransformMeshFilter->GetOutput());
}

} // namespace selx

#endif // selxDisplacementFieldWarperComponent_h