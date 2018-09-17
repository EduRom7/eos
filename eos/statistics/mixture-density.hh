#ifndef EOS_STATISTICS_MIXTURE_DENSITY_HH
#define EOS_STATISTICS_MIXTURE_DENSITY_HH

#include <eos/utils/density.hh>
#include <vector>

namespace eos
{
  class MixtureDensity : public Density
  {
    using MixtureDensityPtr = std::shared_ptr<MixtureDensity>;
    std::vector<double> weights;
    

    
    void evaluate(){
      //Take a Component, evaluate it and multiply it by its weight; then add it to a sum of evaluated components. Use shared pointer to go through all components.
      };

    class Component : public MixtureDensity
{
  virtual void evaluate() = 0;
};

#endif 
