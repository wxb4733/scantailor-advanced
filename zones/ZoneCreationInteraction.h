/*
    Scan Tailor - Interactive post-processing tool for scanned pages.
    Copyright (C) 2007-2009  Joseph Artsimovich <joseph_a@mail.ru>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ZONE_CREATION_INTERACTION_H_
#define ZONE_CREATION_INTERACTION_H_

#include <QCoreApplication>
#include <QDateTime>
#include <QPointF>
#include "BasicSplineVisualizer.h"
#include "DragHandler.h"
#include "DragWatcher.h"
#include "EditableSpline.h"
#include "InteractionHandler.h"
#include "InteractionState.h"
#include "ZoomHandler.h"

class ZoneInteractionContext;

class ZoneCreationInteraction : public InteractionHandler {
  Q_DECLARE_TR_FUNCTIONS(ZoneCreationInteraction)
 public:
  ZoneCreationInteraction(ZoneInteractionContext& context, InteractionState& interaction);

 protected:
  ZoneInteractionContext& context() { return m_context; }

  void onPaint(QPainter& painter, const InteractionState& interaction) override;

  void onKeyPressEvent(QKeyEvent* event, InteractionState& interaction) override;

  void onMousePressEvent(QMouseEvent* event, InteractionState& interaction) override;

  void onMouseReleaseEvent(QMouseEvent* event, InteractionState& interaction) override;

  void onMouseMoveEvent(QMouseEvent* event, InteractionState& interaction) override;

 private:
  void updateStatusTip();

  bool isDragHandlerPermitted(const InteractionState& interaction) const;

  ZoneInteractionContext& m_context;

  /**
   * We have our own drag handler even though there is already a global one
   * for the purpose of being able to monitor it with DragWatcher.  Because
   * we capture a state in the constructor, it's guaranteed the global
   * drag handler will not be functioning until we release the state.
   */
  DragHandler m_dragHandler;

  /**
   * This must go after m_dragHandler, otherwise DragHandler's destructor
   * will try to destroy this object.
   */
  DragWatcher m_dragWatcher;

  /**
   * Because we hold an interaction state from constructor to destructor,
   * we have to have our own zoom handler with explicit interaction permission
   * if we want zoom to work.
   */
  ZoomHandler m_zoomHandler;

  BasicSplineVisualizer m_visualizer;
  InteractionState::Captor m_interaction;
  EditableSpline::Ptr m_spline;
  QPointF m_nextVertexImagePos;
  bool m_rectangularZoneType;
  QPointF m_nextVertexImagePos_mid1;
  QPointF m_nextVertexImagePos_mid2;
  bool m_lassoMode;
  Qt::KeyboardModifiers m_lassoModeModifiers;
};


#endif  // ifndef ZONE_CREATION_INTERACTION_H_
