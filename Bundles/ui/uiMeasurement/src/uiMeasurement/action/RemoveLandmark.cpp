/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2018.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "uiMeasurement/action/RemoveLandmark.hpp"

#include <fwCore/base.hpp>

#include <fwData/Image.hpp>
#include <fwData/Point.hpp>
#include <fwData/PointList.hpp>
#include <fwData/String.hpp>
#include <fwData/Vector.hpp>

#include <fwDataTools/fieldHelper/Image.hpp>
#include <fwDataTools/fieldHelper/MedicalImageHelpers.hpp>

#include <fwGui/dialog/SelectorDialog.hpp>

#include <fwServices/macros.hpp>

#include <boost/lexical_cast.hpp>

#include <exception>
#include <sstream>

namespace uiMeasurement
{
namespace action
{

fwServicesRegisterMacro( ::fwGui::IActionSrv, ::uiMeasurement::action::RemoveLandmark, ::fwData::Image );

static const ::fwServices::IService::KeyType s_IMAGE_INOUT = "image";

//------------------------------------------------------------------------------

RemoveLandmark::RemoveLandmark( ) noexcept
{
}

//------------------------------------------------------------------------------

RemoveLandmark::~RemoveLandmark() noexcept
{
}

//------------------------------------------------------------------------------

void RemoveLandmark::info(std::ostream& _sstream )
{
    _sstream << "Action for remove landmark" << std::endl;
}

//------------------------------------------------------------------------------

::fwData::Point::sptr RemoveLandmark::getLandmarkToRemove(::fwData::Image::sptr image, bool& removeAll)
{
    ::fwData::Point::sptr landmarkToRemove;
    removeAll = false;

    ::fwData::PointList::sptr landmarksBackup = image->getField< ::fwData::PointList >(
        ::fwDataTools::fieldHelper::Image::m_imageLandmarksId );
    SLM_ASSERT("No Field ImageLandmarks", landmarksBackup);

    std::vector< std::string > selections;
    selections.push_back("ALL");
    std::map< std::string, ::fwData::Point::sptr > correspondance;

    for(::fwData::Point::sptr landmark :  landmarksBackup->getPoints())
    {
        ::fwData::String::sptr name = landmark->getField< ::fwData::String >(
            ::fwDataTools::fieldHelper::Image::m_labelId);
        SLM_ASSERT("No Field LabelId", name);
        selections.push_back( *name );
        correspondance[ *name ] = landmark;
    }

    ::fwGui::dialog::SelectorDialog::sptr selector = ::fwGui::dialog::SelectorDialog::New();
    selector->setTitle("Select a landmark to remove");
    selector->setSelections(selections);
    std::string selection = selector->show();
    if( !selection.empty() )
    {
        if (selection == "ALL")
        {
            removeAll = true;
        }
        else
        {
            removeAll        = false;
            landmarkToRemove = correspondance[selection];
        }
    }

    return landmarkToRemove;
}

//------------------------------------------------------------------------------

void RemoveLandmark::notify( ::fwData::Image::sptr image, ::fwData::Point::sptr backup)
{
    auto sig = image->signal< ::fwData::Image::LandmarkRemovedSignalType >(::fwData::Image::s_LANDMARK_REMOVED_SIG);
    sig->asyncEmit(backup);
}

//------------------------------------------------------------------------------

void RemoveLandmark::updating( )
{
    ::fwData::Image::sptr image = this->getInOut< ::fwData::Image >(s_IMAGE_INOUT);
    if (!image)
    {
        FW_DEPRECATED_KEY(s_IMAGE_INOUT, "inout", "18.0");
        image = this->getObject< ::fwData::Image >();
    }
    ::fwData::PointList::sptr landmarks = image->getField< ::fwData::PointList >(
        ::fwDataTools::fieldHelper::Image::m_imageLandmarksId );

    if (::fwDataTools::fieldHelper::MedicalImageHelpers::checkImageValidity(image) && landmarks)
    {
        if (!landmarks->getPoints().empty())
        {
            bool requestAll;
            ::fwData::Point::sptr landmarkToRemove = this->getLandmarkToRemove(image, requestAll );

            // perform action only available distance
            if ( landmarkToRemove )
            {

                ::fwData::PointList::PointListContainer::iterator itr;
                itr = std::find( landmarks->getPoints().begin(), landmarks->getPoints().end(), landmarkToRemove );
                if (itr != landmarks->getPoints().end())
                {
                    landmarks->getPoints().erase(itr);
                    this->notify(image, landmarkToRemove);
                }
            }
            if ( requestAll )
            {
                // backup
                image->removeField( ::fwDataTools::fieldHelper::Image::m_imageLandmarksId ); // erase field
                this->notify(image, landmarkToRemove);
            }
        }
    }
}

//------------------------------------------------------------------------------

void RemoveLandmark::configuring()
{
    this->::fwGui::IActionSrv::initialize();
}

//------------------------------------------------------------------------------

void RemoveLandmark::starting()
{
    this->::fwGui::IActionSrv::actionServiceStarting();
}

//------------------------------------------------------------------------------

void RemoveLandmark::stopping()
{
    this->::fwGui::IActionSrv::actionServiceStopping();
}

//------------------------------------------------------------------------------

} // namespace action
} // namespace uiMeasurement
