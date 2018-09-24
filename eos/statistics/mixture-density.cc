#include <eos/statistics/mixture-density.hh>
#include <eos/utils/private_implementation_pattern-impl.hh>

#include <vector>

namespace eos
{
    template <>
    struct Implementation<MixtureDensity>
    {
        std::vector<double> weights;
        std::vector<MixtureDensity::ComponentPtr> components;

        double evaluate() const
        {
            double result = 0.0;

            auto w = weights.cbegin();
            auto c = components.cbegin();
            for ( ; w != weights.cend() ; ++w, ++c)
            {
                result += *w * (*c)->evaluate();
            }

            return result;
        }
    };

    MixtureDensity::MixtureDensity() :
        PrivateImplementationPattern<MixtureDensity>(new Implementation<MixtureDensity>())
    {
    }

    double
    MixtureDensity::evaluate() const
    {
        return _imp->evaluate();
    }
}

