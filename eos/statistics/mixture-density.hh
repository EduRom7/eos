#ifndef EOS_STATISTICS_MIXTURE_DENSITY_HH
#define EOS_STATISTICS_MIXTURE_DENSITY_HH

#include <eos/utils/density.hh>

class MixtureDensity : public Density
{
};
class Component : public MixtureDensity
{
  virtual void fnct() = 0;
};
