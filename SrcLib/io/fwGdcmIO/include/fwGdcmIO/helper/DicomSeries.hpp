/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2018.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#pragma once

#include "fwGdcmIO/config.hpp"

#include <fwCore/macros.hpp>

#include <boost/filesystem/path.hpp>

#include <gdcmDataSet.h>
#include <gdcmScanner.h>

#include <cstdint>
#include <vector>

namespace fwMedData
{
class DicomSeries;
}

namespace fwMedData
{
class Patient;
class Study;
class Equipment;
}

namespace fwJobs
{
class Observer;
}

namespace fwGdcmIO
{
namespace helper
{

/**
 * @brief DicomSeries Helper. This class is used to generate/fill DicomSeries.
 * - It can be used to read DicomSeries from a list of files (using read function).
 * - It can be used to complete DicomSeries that have been created using the
 *   DicomDir helper (using complete function).
 */
class FWGDCMIO_CLASS_API DicomSeries
{
public:

    typedef std::vector< ::boost::filesystem::path > FilenameContainerType;
    typedef std::vector< SPTR(::fwMedData::DicomSeries) > DicomSeriesContainerType;

    /// Constructor
    FWGDCMIO_API DicomSeries();

    /// Destructor
    FWGDCMIO_API ~DicomSeries();

    /**
     * @brief Read DicomSeries from paths.
     * @param[in] filenames instance paths
     * @param[in] readerObserver reader observer
     * @param[in] completeSeriesObserver complete series observer
     * @return container containing DicomSeries
     */
    FWGDCMIO_API DicomSeriesContainerType read(FilenameContainerType& filenames,
                                               const SPTR(::fwJobs::Observer)& readerObserver         = nullptr,
                                               const SPTR(::fwJobs::Observer)& completeSeriesObserver = nullptr);
    /**
     * @brief Fill DicomSeries information for series generated using DICOMDIR helper
     * @param[in,out] seriesDB List of DicomSeries that must be completed with information
     * @param[in] completeSeriesObserver complete series observer
     */
    FWGDCMIO_API void complete(DicomSeriesContainerType& seriesDB,
                               const SPTR(::fwJobs::Observer)& completeSeriesObserver);

protected:

    /**
     * @brief Fill series with information contained in first instance
     * @param[in,out] seriesDB List of DicomSeries that must be completed with information
     * @param[in] completeSeriesObserver complete series observer
     */
    void fillSeries(DicomSeriesContainerType& seriesDB, const SPTR(::fwJobs::Observer)& completeSeriesObserver);

    /**
     * @brief Create DicomSeries from list of files. Every instance is read in
     * order to retrieve instance information regarding the matching series.
     * @param[in] filenames List of files
     * @param[in] readerObserver reader observer
     */
    DicomSeriesContainerType splitFiles(FilenameContainerType& filenames,
                                        const SPTR(::fwJobs::Observer)& readerObserver);

    /**
     * @brief Create a series from the dataset and store it in the series map
     * @param[in,out] seriesDB List of DicomSeries that must be completed with information
     * @param[in] scanner GDCM Scanner used to read information
     * @param[in] filename Filename from which the information must be read
     */
    void createSeries(DicomSeriesContainerType& seriesDB,
                      const ::gdcm::Scanner& scanner,
                      const ::boost::filesystem::path& filename);

    /**
     * @brief Create a patient from the dataset and store it in the patient map
     * @param[in] dataset GDCM Dataset used to read information
     */
    SPTR(::fwMedData::Patient) createPatient(const ::gdcm::DataSet& dataset);

    /**
     * @brief Create a study from the dataset and store it in the study map
     * @param[in] dataset GDCM Dataset used to read information
     */
    SPTR(::fwMedData::Study) createStudy(const ::gdcm::DataSet& dataset);

    /**
     * @brief Create an equipment from the dataset and store it in the equipment map
     * @param[in] dataset GDCM Dataset used to read information
     */
    SPTR(::fwMedData::Equipment) createEquipment(const ::gdcm::DataSet& dataset);

    typedef std::map< std::string, SPTR(::fwMedData::Patient) > PatientMapType;
    typedef std::map< std::string, SPTR(::fwMedData::Study) > StudyMapType;
    typedef std::map< std::string, SPTR(::fwMedData::Equipment) > EquipmentMapType;

    ///Patient Map
    PatientMapType m_patientMap;

    ///Study Map
    StudyMapType m_studyMap;

    ///Equipment Map
    EquipmentMapType m_equipmentMap;
};

} //helper
} //fwGdcmIO
