/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
 * Copyright (c) 2011 Frederik Beaujean
 *
 * This file is part of the EOS project. EOS is free software;
 * you can redistribute it and/or modify it under the terms of the GNU General
 * Public License version 2, as published by the Free Software Foundation.
 *
 * EOS is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef EOS_GUARD_SRC_UTILS_ANALYSIS_HH
#define EOS_GUARD_SRC_UTILS_ANALYSIS_HH 1

#include <src/utils/analysis-fwd.hh>
#include <src/utils/log_likelihood.hh>
#include <src/utils/log_prior.hh>
#include <src/utils/private_implementation_pattern.hh>
#include <src/utils/verify.hh>

#include <vector>
#include <set>

#include <gsl/gsl_multimin.h>

namespace eos
{
    class Analysis :
        public PrivateImplementationPattern<Analysis>
    {
        public:
            struct OptimizationOptions;

            ///@name Basic Functions
            ///@{
            /*!
             * Constructor.
             *
             * Extracts parameters, observables from LogLikelihood.
             * The default prior (flat) is assumed for all parameters.
             *
             * @param log_likelihood  The LogLikelihood functor which shall be analysed.
             *
             * @note Analysis assumes ownership of log_likelihood
             */
            Analysis(const LogLikelihoodPtr & log_likelihood);

            /// Destructor.
            ~Analysis();

            /// Clone this Analysis
            AnalysisPtr clone() const;
            ///@}

            ///@name Accessors
            ///@{
            /// Retrieve a set of all parameters, including ranges
            const std::vector<ParameterDescription> & parameter_descriptions() const;

            /*!
             * Retrieve a parameter by index.
             *
             * @param index The index of the parameter.
             */
            Parameter operator[] (const unsigned & index);

            /// Retrieve our associates Parameters object
            Parameters parameters() const;

            /*!
             * Add one or more parameters and associated prior density
             *
             * @param prior    The logarithmic prior density.
             * @param nuisance False for a parameter of interest
             */
            bool add(const LogPriorPtr & prior, bool nuisance = false);

            /// Retrieve the overall Log(likelihood) for this analysis.
            LogLikelihoodPtr & log_likelihood();

            /// Retrieve the overall Log(prior) for this analysis.
            double log_prior();

            /*!
             * Find the prior for a given parameter
             */
            LogPriorPtr log_prior(const std::string & name) const;

            /// Retrieve the overall Log(posterior) for this analysis.
            ///   incorporate normalization constant, the evidence here in getter if available
            double log_posterior();

            /*!
             * Check if a given parameter is a nuisance parameter for this Analysis.
             *
             * @param name The name of the parameter we are interested in.
             */
            bool nuisance(const std::string & name) const;
            ///@}

            /*!
             * Optimize the posterior using the Nelder-Mead simplex algorithm.
             * @param initial_guess Starting point for simplex construction
             * @param options If no tuning desired, use Analysis::OptimizationOptions::Defaults()
             * @return <parameter values at mode, posterior value at mode>
             */
            std::pair<std::vector<double>, double>
            optimize(const std::vector<double> & initial_guess, const OptimizationOptions & options);
    };

        struct Analysis::OptimizationOptions
        {
                /// Fraction of parameter range, in [0,1].
                VerifiedRange<double> initial_step_size;

                /// If algorithm doesn't converge before, quit
                /// after maximum_iterations.
                unsigned maximum_iterations;

                /// Once the algorithm has shrunk the probe
                /// simplex below this size, convergence is declared.
                VerifiedRange<double> maximum_simplex_size;

                OptimizationOptions();

                static OptimizationOptions Defaults();
        };
}

#endif
