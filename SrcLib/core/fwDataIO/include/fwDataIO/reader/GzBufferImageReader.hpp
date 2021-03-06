/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2017.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __FWDATAIO_READER_GZBUFFERIMAGEREADER_HPP__
#define __FWDATAIO_READER_GZBUFFERIMAGEREADER_HPP__

#include "fwDataIO/config.hpp"
#include "fwDataIO/reader/GenericObjectReader.hpp"

#include <fwData/Image.hpp>
#include <fwData/location/SingleFile.hpp>

#include <boost/filesystem/path.hpp>

namespace fwDataIO
{

namespace reader
{

/**
 * @brief   Image Reader. Read file format .raw.gz
 *
 *
 * Ircad reader to read a ::fwData::Image on filesystem which the file format
 * is .raw.gz. This format is basic. The buffer is writen in a file with zlib.
 */
class FWDATAIO_CLASS_API GzBufferImageReader :  public GenericObjectReader< ::fwData::Image >,
                                                public ::fwData::location::enableSingleFile< IObjectReader >
{

public:

    fwCoreClassDefinitionsWithFactoryMacro((GzBufferImageReader)(GenericObjectReader< ::fwData::Image>),
                                           (()),
                                           ::fwDataIO::reader::factory::New< GzBufferImageReader >
                                           );

    /// Constructor. Do nothing.
    FWDATAIO_API GzBufferImageReader(::fwDataIO::reader::IObjectReader::Key key);

    /// Destructor. Do nothing.
    FWDATAIO_API virtual ~GzBufferImageReader();

    /// Read the file with zlib API.
    FWDATAIO_API virtual void read() override;

    /// Defines extension supported by this reader ".raw.gz"
    FWDATAIO_API std::string extension() override;

};

} // namespace reader

} // namespace fwDataIO

#endif // __FWDATAIO_READER_GZBUFFERIMAGEREADER_HPP__
