#ifndef EOS_STATISTICS_MIXTURE_DENSITY_HH
#define EOS_STATISTICS_MIXTURE_DENSITY_HH

#include <eos/utils/density.hh>
#include <eos/utils/private_implementation_pattern.hh>

namespace eos
{
    class MixtureDensity :
        public Density,
        public PrivateImplementationPattern<MixtureDensity>
    {
        public:
            class Component;
            using ComponentPtr = std::shared_ptr<MixtureDensity::Component>;

            class MultivariateGaussianComponent;

            MixtureDensity();
            ~MixtureDensity() = default;

            // Returns the (normalized) PDF on a logarithmic scale
            virtual double evaluate() const override;
    };

    class MixtureDensity::Component :
        public Density
    {
        public:
            // Returns the (normalized) PDF on a logarithmic scale
            virtual double evaluate() const = 0;
    };

    class MixtureDensity::UnivariateGaussianComponent :
        public MixtureDensity::Component,
		public PrivateImplementationPattern<MixtureDensity::UnivariateGaussianComponent>
    {
        public:
            // Returns the (normalized) PDF on a logarithmic scale
            virtual double evaluate() const override;
            UnivariateGaussianComponent(double mean, double variance);
    };
}

#endif 
