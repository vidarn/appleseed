
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2010-2012 Francois Beaune, Jupiter Jazz Limited
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#ifndef APPLESEED_STUDIO_MAINWINDOW_PROJECT_INSTANCECOLLECTIONITEM_H
#define APPLESEED_STUDIO_MAINWINDOW_PROJECT_INSTANCECOLLECTIONITEM_H

// appleseed.studio headers.
#include "mainwindow/project/collectionitembase.h"

// appleseed.foundation headers.
#include "foundation/platform/compiler.h"
#include "foundation/utility/uid.h"

// Standard headers.
#include <cassert>

// Forward declarations.
namespace appleseed { namespace studio { class ItemBase; } }
namespace appleseed { namespace studio { class ProjectBuilder; } }
class QString;

namespace appleseed {
namespace studio {

template <typename Entity, typename EntityItem, typename ParentEntity, typename ParentItem>
class InstanceCollectionItem
  : public CollectionItemBase<Entity>
{
  public:
    InstanceCollectionItem(
        const foundation::UniqueID  class_uid,
        const QString&              title,
        ParentEntity&               parent,
        ParentItem*                 parent_item,
        ProjectBuilder&             project_builder);

  private:
    ParentEntity&                   m_parent;
    ParentItem*                     m_parent_item;
    ProjectBuilder&                 m_project_builder;

    virtual ItemBase* create_item(Entity* entity) const override;
};


//
// InstanceCollectionItem class implementation.
//

template <typename Entity, typename EntityItem, typename ParentEntity, typename ParentItem>
InstanceCollectionItem<Entity, EntityItem, ParentEntity, ParentItem>::InstanceCollectionItem(
    const foundation::UniqueID      class_uid,
    const QString&                  title,
    ParentEntity&                   parent,
    ParentItem*                     parent_item,
    ProjectBuilder&                 project_builder)
  : CollectionItemBase<Entity>(class_uid, title)
  , m_parent(parent)
  , m_parent_item(parent_item)
  , m_project_builder(project_builder)
{
}

template <typename Entity, typename EntityItem, typename ParentEntity, typename ParentItem>
ItemBase* InstanceCollectionItem<Entity, EntityItem, ParentEntity, ParentItem>::create_item(Entity* entity) const
{
    assert(entity);

    return
        new EntityItem(
            entity,
            m_parent,
            m_parent_item,
            m_project_builder);
}

}       // namespace studio
}       // namespace appleseed

#endif  // !APPLESEED_STUDIO_MAINWINDOW_PROJECT_INSTANCECOLLECTIONITEM_H