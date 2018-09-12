#ifndef EOS_STATISTICS_MIXTURE_DENSITY_HH
#define EOS_STATISTICS_MIXTURE_DENSITY_HH

#include <eos/utils/density.hh>
#include <vector>

namespace eos
{
  class MixtureDensity : public Density
  {
    using MixtureDensityPtr = std::shared_ptr<MixtureDensity>;
    void evaluate(){ //Take a Component, evaluate it and add it to a sum of values. Use shared pointer to go through all components.
      
};
class Component : public MixtureDensity
{
  virtual void evaluate() = 0;
};

#endif 
