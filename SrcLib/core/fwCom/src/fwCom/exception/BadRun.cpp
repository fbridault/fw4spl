/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include <fwCore/Exception.hpp>

#include "fwCom/config.hpp"
#include "fwCom/exception/BadRun.hpp"

namespace fwCom
{

namespace exception
{

BadRun::BadRun ( const std::string &err ) : ::fwCore::Exception(err)
{
}

} // namespace exception

} // namespace fwCom


