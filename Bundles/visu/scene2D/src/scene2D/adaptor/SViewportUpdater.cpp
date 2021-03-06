/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2017.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "scene2D/adaptor/SViewportUpdater.hpp"

#include <fwRenderQt/data/Viewport.hpp>
#include <fwRenderQt/Scene2DGraphicsView.hpp>

#include <fwServices/macros.hpp>

fwServicesRegisterMacro( ::fwRenderQt::IAdaptor, ::scene2D::adaptor::SViewportUpdater);

namespace scene2D
{
namespace adaptor
{

static const ::fwServices::IService::KeyType s_VIEWPORT_INPUT = "viewport";

SViewportUpdater::SViewportUpdater() noexcept
{
}

//-----------------------------------------------------------------------------

SViewportUpdater::~SViewportUpdater() noexcept
{
}

//-----------------------------------------------------------------------------

void SViewportUpdater::configuring()
{
    this->configureParams();
}

//-----------------------------------------------------------------------------

void SViewportUpdater::starting()
{
    updating();
}

//-----------------------------------------------------------------------------

void SViewportUpdater::stopping()
{
}

//-----------------------------------------------------------------------------

void SViewportUpdater::updating()
{
    ::fwRenderQt::data::Viewport::sptr sceneViewport   = this->getScene2DRender()->getViewport();
    ::fwRenderQt::data::Viewport::csptr viewportObject =
        this->getInput< ::fwRenderQt::data::Viewport>(s_VIEWPORT_INPUT);

    Point2DType pairCoord = this->mapAdaptorToScene(
        Point2DType(viewportObject->getX(), viewportObject->getY() ), m_xAxis, m_yAxis );

    Point2DType pairSize = this->mapAdaptorToScene(
        Point2DType(viewportObject->getWidth(), viewportObject->getHeight() ), m_xAxis, m_yAxis );

    sceneViewport->setX( pairCoord.first );
    sceneViewport->setY( pairCoord.second );
    sceneViewport->setWidth( pairSize.first );
    sceneViewport->setHeight( viewportObject->getHeight() );

    this->getScene2DRender()->getView()->updateFromViewport();
}

//-----------------------------------------------------------------------------

void SViewportUpdater::processInteraction( ::fwRenderQt::data::Event& _event )
{

}

//----------------------------------------------------------------------------------------------------------

::fwServices::IService::KeyConnectionsMap SViewportUpdater::getAutoConnections() const
{
    KeyConnectionsMap connections;
    connections.push( s_VIEWPORT_INPUT, ::fwRenderQt::data::Viewport::s_MODIFIED_SIG, s_UPDATE_SLOT );
    return connections;
}

}   // namespace adaptor
}   // namespace scene2D

