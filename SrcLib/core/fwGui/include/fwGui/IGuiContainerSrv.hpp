/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __FWGUI_IGUICONTAINERSRV_HPP__
#define __FWGUI_IGUICONTAINERSRV_HPP__

#include "fwGui/config.hpp"
#include "fwGui/container/fwContainer.hpp"
#include "fwGui/registrar/ViewRegistrar.hpp"
#include "fwGui/layoutManager/IViewLayoutManager.hpp"
#include "fwGui/builder/IToolBarBuilder.hpp"
#include "fwGui/builder/IContainerBuilder.hpp"

#include <fwCom/Slot.hpp>
#include <fwCom/Slots.hpp>

#include <fwServices/IService.hpp>


namespace fwGui
{

/**
 * @brief   Defines the service interface managing the layout.
 *
 * @section Slots Slots
 *
 * - \b setEnabled(bool isEnabled) : this slot enables the container (if isEnabled = true) or disables it.
 * - \b enable() : this slot enables the container.
 * - \b disable() : this slot disables the container
 * - \b setVisible(bool isVisible) : this slot shows the container (if isVisible = true) or hides it.
 * - \b show() : this slot shows the container.
 * - \b hide() : this slot hides the container.
 *
 * @section XML Example of XML configuration
 *
 * @code{.xml}
   <service uid="subView1" type="::gui::view::IView" impl="::gui::view::SDefaultView" autoConnect="no" >
       <gui>
           <layout type="::fwGui::LineLayoutManager" >
               <orientation value="horizontal" />
               <view caption="view3" />
               <view caption="view4" />
               <view caption="view5" />
           </layout>
           <toolBar />
       </gui>
       <registry>
           <parent wid="myView" />
           <toolBar sid="toolbar1" start="yes" />
           <view sid="subView3" start="yes" />
           <view wid="subView4" />
           <view sid="subView5" />
       </registry>
   </service>
   @endcode
 *  - \<layout type="::fwGui::LineLayoutManager" \> : give the type of layout.
 *    - \b type {::fwGui::LineLayoutManager |::fwGui::CardinalLayoutManager |::fwGui::TabLayoutManager |::fwGui::ToolboxLayoutManager} :
 *     - \b ::fwGui::LineLayoutManager : all views will be on the same line or column (it depends of the orientation value attribute)
 *           @see ::fwGui::layoutManager::LineLayoutManagerBase
 *     - \b ::fwGui::CardinalLayoutManager : all views will be added around a central view define by the align attribute.
 *           @see ::fwGui::layoutManager::CardinalLayoutManagerBase
 *     - \b ::fwGui::TabLayoutManager : all views will be draw as tab.
 *           @see ::fwGui::layoutManager::TabLayoutManagerBase
 *     - \b ::fwGui::ToolboxLayoutManager : all views will be draw in toolbox.
 *           @see ::fwGui::layoutManager::ToolboxLayoutManagerBase
 *  - The toolBar section isn't mandatory.
 *
 * @note The layout and registry sections can be empty. In this case no subview will be created.
 *
 * @warning
 * - The order of the view in each section (gui and registry) must be the same.\n
 *   For example: the view caption "view3" will be connected with the service which have the sid = "subView3" and so one (it also could be a wid).
 *
 *
 */
class FWGUI_CLASS_API IGuiContainerSrv : public ::fwServices::IService
{

public:

    fwCoreServiceClassDefinitionsMacro ( (IGuiContainerSrv)(::fwServices::IService) );

    FWGUI_API ::fwGui::container::fwContainer::sptr getContainer();

    FWGUI_API void setParent(std::string wid);

protected:

    FWGUI_API IGuiContainerSrv();

    FWGUI_API virtual ~IGuiContainerSrv();

    typedef ::fwRuntime::ConfigurationElement::sptr ConfigurationType;

    /**
     * @brief Initialize managers.
     *
       @see ::fwGui::registrar::ViewRegistrar::initialize(), ::fwGui::layoutManager::IViewLayoutManager::initialize(), ::fwGui::builder::IToolBarBuilder::initialize()
     */
    FWGUI_API void initialize();

    /**
     * @brief Creates view, sub-views and toolbar containers. Manages sub-views and toobar services.
     *
     * @pre Parent container must be registered.
     */
    FWGUI_API void create();

    /// Stops sub-views and toobar services. Destroys view, sub-views and toolbar containers.
    FWGUI_API void destroy();

    /**
     * @name Slots Keys
     * @{
     */
    /// Slot to enable/disable the action
    static const ::fwCom::Slots::SlotKeyType s_SET_ENABLED_SLOT;

    /// Slot to enable the container
    static const ::fwCom::Slots::SlotKeyType s_ENABLE_SLOT;

    /// Slot to disable the container
    static const ::fwCom::Slots::SlotKeyType s_DISABLE_SLOT;

    /// Slot to show/hide the container
    static const ::fwCom::Slots::SlotKeyType s_SET_VISIBLE_SLOT;

    /// Slot to show the container
    static const ::fwCom::Slots::SlotKeyType s_SHOW_SLOT;

    /// Slot to hide the container
    static const ::fwCom::Slots::SlotKeyType s_HIDE_SLOT;
    /**
     * @}
     */

private:

    /// SLOT: enable/disable the container
    void setEnabled(bool isEnabled);
    /// SLOT: enable the container
    void enable();
    /// SLOT: disable the container
    void disable();
    /// SLOT: show/hide the container
    void setVisible(bool isVisible);
    /// SLOT: show the container
    void show();
    /// SLOT: hide the container
    void hide();

    void initializeLayoutManager( ::fwRuntime::ConfigurationElement::sptr layoutConfig );
    void initializeToolBarBuilder( ::fwRuntime::ConfigurationElement::sptr toolBarConfig );

    bool m_viewLayoutManagerIsCreated;
    ::fwGui::layoutManager::IViewLayoutManager::sptr m_viewLayoutManager;

    ::fwGui::registrar::ViewRegistrar::sptr m_viewRegistrar;
    ::fwGui::builder::IToolBarBuilder::sptr m_toolBarBuilder;
    ::fwGui::builder::IContainerBuilder::sptr m_containerBuilder;

    ConfigurationType m_viewRegistrarConfig;
    ConfigurationType m_viewLayoutConfig;
    ConfigurationType m_toolBarConfig;

    bool m_hasToolBar;
};

} // namespace fwGui

#endif /*__FWGUI_IGUICONTAINERSRV_HPP__*/


