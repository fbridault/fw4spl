/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "SlotsTest.hpp"

#include <fwCom/HasSlots.hpp>

#include <fwCom/Slots.hpp>
#include <fwCom/Slots.hxx>
#include <fwTest/Exception.hpp>

#include <fwThread/Worker.hpp>

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( ::fwCom::ut::SlotsTest );

namespace fwCom
{
namespace ut
{

static ::fwTest::Exception fwTestException(""); // force link with fwTest

void SlotsTest::setUp()
{
    // Set up context before running a test.

}
void SlotsTest::tearDown()
{
    // Clean up after the test run.
}

int slotsTestSum (int a, int b)
{
    return a+b;
}

void slotsTestPrint(const std::string &str)
{
    SLM_TRACE(str);
}

struct SlotsTestBasic
{
    SlotsTestBasic()
    {
    }

    int sum(int a, int b)
    {
        return a+b;
    }
};

//-----------------------------------------------------------------------------

void SlotsTest::buildTest()
{
    ::fwCom::Slots slots;

    ::fwCom::Slot< int (int, int) >::sptr slot1             = ::fwCom::newSlot( &slotsTestSum );
    ::fwCom::Slot< void (const std::string &) >::sptr slot2 = ::fwCom::newSlot( &slotsTestPrint );

    slots("sum", std::dynamic_pointer_cast< SlotBase >(slot1))
        ("print", std::dynamic_pointer_cast< SlotBase >(slot2))
        ("another_key", slot1);

    CPPUNIT_ASSERT(slot1 == slots["sum"]);
    CPPUNIT_ASSERT(slot2 == slots["print"]);
    CPPUNIT_ASSERT(slots["sum"] == slots["another_key"]);
    CPPUNIT_ASSERT(!slots["wrong_slot"]);


    SlotsTestBasic slotsBasicStruct;
    slots("struct_sum", &SlotsTestBasic::sum, &slotsBasicStruct);

    CPPUNIT_ASSERT_EQUAL(14, slots["struct_sum"]->call<int>(5,9));

    ::fwThread::Worker::sptr worker = ::fwThread::Worker::New();

    slots.setWorker(worker);

    int count = 0;
    for(::fwCom::Slots::SlotKeyType key :  slots.getSlotKeys())
    {
        ::fwCom::SlotBase::sptr slot = slots[key];
        CPPUNIT_ASSERT(worker == slot->getWorker());
        ++count;
    }
    CPPUNIT_ASSERT_EQUAL(4, count);
}

//-----------------------------------------------------------------------------

struct SlotsTestHasSlots : public HasSlots
{
    typedef Slot< int ()> GetValueSlotType;

    SlotsTestHasSlots()
    {
        GetValueSlotType::sptr slotGetValue = ::fwCom::newSlot( &SlotsTestHasSlots::getValue, this );

        HasSlots::m_slots("sum", &SlotsTestHasSlots::sum, this)
            ("getValue", slotGetValue );
    }

    int sum(int a, int b)
    {
        return a+b;
    }

    int getValue()
    {
        return 4;
    }
};

//-----------------------------------------------------------------------------

struct SlotsTestHasSlots2 : public HasSlots
{
    typedef Slot< int ()> GetValueSlotType;

    SlotsTestHasSlots2()
    {
        newSlot( "sum", &SlotsTestHasSlots2::sum, this );

        GetValueSlotType::sptr slot = newSlot( "getValue", &SlotsTestHasSlots2::getValue, this );
        CPPUNIT_ASSERT(slot);
    }

    int sum(int a, int b)
    {
        return a+b;
    }

    int getValue()
    {
        return 4;
    }
};

//-----------------------------------------------------------------------------

void SlotsTest::hasSlotsTest()
{
    SlotsTestHasSlots obj;
    CPPUNIT_ASSERT_EQUAL(14, obj.slot("sum")->call<int>(5,9));
    CPPUNIT_ASSERT_EQUAL(4, obj.slot< SlotsTestHasSlots::GetValueSlotType >("getValue")->call());

    SlotsTestHasSlots2 obj2;
    CPPUNIT_ASSERT_EQUAL(14, obj2.slot("sum")->call<int>(5,9));
    CPPUNIT_ASSERT_EQUAL(4, obj2.slot< SlotsTestHasSlots::GetValueSlotType >("getValue")->call());
}

//-----------------------------------------------------------------------------

void SlotsTest::slotsIDTest()
{

}

//-----------------------------------------------------------------------------
} //namespace ut
} //namespace fwCom
