
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2010-2013 Francois Beaune, Jupiter Jazz Limited
// Copyright (c) 2014 Francois Beaune, The appleseedhq Organization
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

#ifndef APPLESEED_RENDERER_KERNEL_RENDERING_GENERIC_TILEJOBFACTORY_H
#define APPLESEED_RENDERER_KERNEL_RENDERING_GENERIC_TILEJOBFACTORY_H

// appleseed.renderer headers.
#include "renderer/kernel/rendering/generic/tilejob.h"

// appleseed.foundation headers.
#include "foundation/math/rng.h"

// Standard headers.
#include <cstddef>
#include <vector>

// Forward declarations.
namespace foundation    { class AbortSwitch; }
namespace foundation    { class CanvasProperties; }
namespace renderer      { class Frame; }
namespace renderer      { class TileJob; }

namespace renderer
{

//
// Creates tile jobs to render a complete frame.
//

class TileJobFactory
{
  public:
    typedef std::vector<TileJob*> TileJobVector;

    // Tile orderings.
    enum TileOrdering
    {
        LinearOrdering,
        SpiralOrdering,
        HilbertOrdering,
        RandomOrdering
    };

    // Create tile jobs for a given frame.
    void create(
        const Frame&                        frame,
        const TileOrdering                  tile_ordering,
        const TileJob::TileRendererVector&  tile_renderers,
        const TileJob::TileCallbackVector&  tile_callbacks,
        const size_t                        pass_hash,
        TileJobVector&                      tile_jobs,
        foundation::AbortSwitch&            abort_switch);

  private:
    foundation::MersenneTwister             m_rng;

    void generate_tile_ordering(
        const foundation::CanvasProperties& frame_properties,
        const TileOrdering                  tile_ordering,
        std::vector<size_t>&                tiles);
};

}       // namespace renderer

#endif  // !APPLESEED_RENDERER_KERNEL_RENDERING_GENERIC_TILEJOBFACTORY_H
