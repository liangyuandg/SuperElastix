#include "GDOptimizer3rdPartyComponent.h"

namespace selx
{
GDOptimizer3rdPartyComponent::GDOptimizer3rdPartyComponent()
{
  this->theImplementation = new Example3rdParty::GDOptimizer3rdParty();
  this->MetricObject = new Metric3rdPartyWrapper();
}
GDOptimizer3rdPartyComponent::~GDOptimizer3rdPartyComponent()
{
  delete this->theImplementation;
  delete this->MetricObject;
}


int GDOptimizer3rdPartyComponent::Set(MetricValueInterface* component)
{
  this->MetricObject->SetMetricValueComponent(component);
  return 0;
}
int GDOptimizer3rdPartyComponent::Set(MetricDerivativeInterface* component)
{
  this->MetricObject->SetMetricDerivativeComponent(component);
  return 0;
}
int GDOptimizer3rdPartyComponent::Update()
{
  this->theImplementation->SetMetric(this->MetricObject);
  return this->theImplementation->Optimize(); // 3rd party specific call
}

bool
GDOptimizer3rdPartyComponent
::MeetsCriterion(const CriterionType &criterion)
{
  bool hasUndefinedCriteria(false);
  bool meetsCriteria(false);
  if (criterion.first == "ComponentProperty")
  {
    meetsCriteria = true;
    for (auto const & criterionValue : criterion.second) // auto&& preferred?
    {
      if (criterionValue != "SomeProperty")  // e.g. "GradientDescent", "SupportsSparseSamples
      {
        meetsCriteria = false;
      }
    }
  }
  return meetsCriteria;
}

} //end namespace selx