/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include <fwData/Composite.hpp>
#include <fwData/camp/mapper.hpp>

#include <fwCamp/UserObject.hpp>
#include <fwCamp/Mapper/ValueMapper.hpp>

fwCampImplementDataMacro((fwData)(Composite))
{
    builder
    .tag("object_version", "1")
    .tag("lib_name", "fwData")
    .base< ::fwData::Object>()
    .property("values", &::fwData::Composite::m_container)
    ;
}
