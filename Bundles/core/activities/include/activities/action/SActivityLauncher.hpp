/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2013.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef _ACTIVITIES_ACTION_SACTIVITYLAUNCHER_HPP_
#define _ACTIVITIES_ACTION_SACTIVITYLAUNCHER_HPP_

#include <fwTools/Failed.hpp>

#include <fwRuntime/ConfigurationElement.hpp>
#include <fwRuntime/EConfigurationElement.hpp>

#include <fwGui/IActionSrv.hpp>
#include <fwActivities/registry/Activities.hpp>

#include "activities/config.hpp"

namespace activities
{
namespace action
{

class ACTIVITIES_CLASS_API SActivityLauncher : public ::fwGui::IActionSrv
{

public :

    fwCoreServiceClassDefinitionsMacro ( (SActivityLauncher)(::fwGui::IActionSrv) ) ;

    /// Constructor. Do nothing.
    ACTIVITIES_API SActivityLauncher() throw() ;

    /// Destructor. Do nothing.
    ACTIVITIES_API virtual ~SActivityLauncher() throw() ;

protected:

    ///This method launches the IAction::starting method.
    virtual void starting() throw(::fwTools::Failed);

    ///This method launches the IAction::stopping method.
    virtual void stopping() throw(::fwTools::Failed);

    /**
     * @brief This method is used to update services on notification. ( overrides ).
     * Enable the action according to the available activities.
     */
    virtual void receiving( CSPTR(::fwServices::ObjectMsg) msg ) throw(::fwTools::Failed);

    /**
     * @brief Show activity selector.
     */
    virtual void updating() throw(::fwTools::Failed);

    /**
     * @brief Initialize the action.
     * @see fwGui::IActionSrv::initialize()
      */
    virtual void configuring() throw(fwTools::Failed);

    /// Overrides
    virtual void info( std::ostream &_sstream ) ;

    /**
     * @brief Updates action state (enable if activities are available for current selection).
     */
    virtual void updateState();

private:

    /// Send message to launch new tab view
    void sendConfig( const ::fwActivities::registry::ActivityInfo & info );

    typedef ::fwActivities::registry::Activities::ActivitiesType ActivityInfoContainer;

    /// Show custom dialog box
    ::fwActivities::registry::ActivityInfo show( const ActivityInfoContainer & infos );
};

} //action
} // gui


#endif // _ACTIVITIES_ACTION_SACTIVITYLAUNCHER_HPP_

