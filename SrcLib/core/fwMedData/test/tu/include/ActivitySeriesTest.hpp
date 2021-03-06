/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __FWMEDDATA_UT_ACTIVITYSERIESTEST_HPP__
#define __FWMEDDATA_UT_ACTIVITYSERIESTEST_HPP__

#include <cppunit/extensions/HelperMacros.h>
#include <fwMedData/ActivitySeries.hpp>

namespace fwMedData
{

namespace ut
{

class ActivitySeriesTest : public CPPUNIT_NS::TestFixture
{
CPPUNIT_TEST_SUITE( ActivitySeriesTest );

CPPUNIT_TEST(activityConfigIdTest);
CPPUNIT_TEST(dataTest);

CPPUNIT_TEST_SUITE_END();

public:
    // interface
    void setUp();
    void tearDown();

    void activityConfigIdTest();
    void dataTest();

protected:

    SPTR(::fwMedData::ActivitySeries) m_series;

};

} //namespace ut
} //namespace fwMedData

#endif //__FWMEDDATA_UT_ACTIVITYSERIESTEST_HPP__

