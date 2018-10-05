/*
 * mixture-density_TEST.cc
 *
 *  Created on: 2 Oct 2018
 *      Author: Eduardo Romero
 */

#include <test/test.hh>
#include <mixture-density.hh>
#include <eos/utils/exception.hh>

using namespace test;
using namespace eos;

class UnivariateGaussianComponentTest : public TestCase {
	UnivariateGaussianComponentTest() : TestCase("univariategaussiancomponent_test")
	virtual void run() const override
	{
	TEST_CHECK_THROWS(InternalError, MixtureDensity::UnivariateGaussianComponent(1, -1));
	TEST_CHECK_NO_THROW(MixtureDensity::UnivariateGaussianComponent(1, 1));
	MixtureDensity::UnivariateGaussianComponent u(1, 1);
	TEST_CHECK_EQUAL(u.evaluate(), 0.0);
	}

}
uvgc_test;

