/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2010.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef _FWSERVICES_REGISTRY_APPCONFIG_HPP_
#define _FWSERVICES_REGISTRY_APPCONFIG_HPP_

#include <map>

#include <fwTools/Object.hpp>
#include <fwTools/macros.hpp>
#include <fwTools/Factory.hpp>

#include "fwServices/config.hpp"

namespace fwServices
{

namespace registry
{


/**
 * @class AppInfo
 * @author  IRCAD (Research and Development Team).
 */
class FWSERVICES_CLASS_API AppInfo : public ::fwCore::BaseObject
{
public :

    enum ConfigType {
        TEMPLATE,
        STANDARD,
    };

    fwCoreClassDefinitionsWithFactoryMacro( (AppInfo)(::fwCore::BaseObject), (()), new AppInfo );

    /// Constructor, do nothing.
    FWSERVICES_API AppInfo(){}

    /// Destructor, do nothing.
    FWSERVICES_API virtual ~AppInfo(){}

    ConfigType type;
    std::string desc;
    ::fwRuntime::ConfigurationElement::csptr config;
};


/**
 * @class AppConfig
 * @author  IRCAD (Research and Development Team).
 */
class FWSERVICES_CLASS_API AppConfig : public ::fwCore::BaseObject
{

public:

    fwCoreClassDefinitionsWithFactoryMacro( (AppConfig)(::fwCore::BaseObject), (()), new AppConfig) ;

    /// Return the unique Instance, create it if required at first access
    FWSERVICES_API static AppConfig::sptr getDefault();

    /// Destructor
    FWSERVICES_API virtual ~AppConfig();

    /// Parse bundle information to retreive service declaration
    FWSERVICES_API void parseBundleInformation();

    FWSERVICES_API void addAppInfo
    (   const std::string & configId,
            AppInfo::ConfigType type,
            const std::string & desc,
            ::fwRuntime::ConfigurationElement::csptr config);

    FWSERVICES_API ::fwRuntime::ConfigurationElement::csptr getStandardConfig( const std::string & configId ) const;

    FWSERVICES_API ::fwRuntime::ConfigurationElement::csptr getAdaptedTemplateConfig( const std::string & configId, const std::map< std::string, std::string > & replaceFields ) const;

    FWSERVICES_API void clearRegistry();

protected :

    typedef std::map< std::string, AppInfo::sptr > Registry;

    /// Container of service information
    Registry m_reg;

    /// Constructor, protected to ensure unique instance (singleton pattern)
    FWSERVICES_API AppConfig();

};

} // namespace registry

} // namespace fwServices

#endif // _FWSERVICES_REGISTRY_APPCONFIG_HPP_


