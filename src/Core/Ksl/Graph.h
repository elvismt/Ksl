/*
 * Copyright (C) 2016  Elvis Teixeira
 *
 * This source code is free software: you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General
 * Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any
 * later version.
 *
 * This source code is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this program.
 * If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KSL_GRAPH_H
#define KSL_GRAPH_H

#include <Ksl/MemoryPool.h>

namespace Ksl {

// Forward declaration
template <typename VertData, typename EdgeData> class GraphEdge;
template <typename VertData, typename EdgeData> class GraphVertex;
template <typename VertData, typename EdgeData> class Graph;



// Base class for edge classes
template <
    typename VertData,
    typename EdgeData=VertData
>
class GraphEdge
{
public:

    typedef GraphVertex<VertData,EdgeData> TVertex;
    typedef Graph<VertData,EdgeData> TGraph;

    GraphEdge(TVertex *source, TVertex *target, const EdgeData &data)
        : m_source(source)
        , m_target(target)
        , m_data(data)
    { }

    EdgeData& data() { return m_data; }
    const EdgeData& data() const { return m_data; }

    TVertex* source() { return m_source; }
    const TVertex* source() const { return m_source; }

    TVertex* target() { return m_target; }
    const TVertex* target() const { return m_target; }

    GraphEdge* next() { return m_next; }
    const GraphEdge* next() const { return m_next; }


private:

    friend class Graph<VertData,EdgeData>;

    TVertex *m_source;
    TVertex *m_target;
    EdgeData m_data;
    GraphEdge *m_next;
};


// Base class for vertex classes
template <
    typename VertData,
    typename EdgeData=VertData
>
class GraphVertex
{
public:

    typedef GraphEdge<VertData,EdgeData> TEdge;
    typedef Graph<VertData,EdgeData> TGraph;

    GraphVertex(const VertData &data)
        : m_edges(nullptr)
        , m_data(data)
    { }

    VertData& data() { return m_data; }
    const VertData& data() const { return m_data; }

    TEdge *firstEdge() { return m_edges; }
    const TEdge *firstEdge() const { return m_edges; }


    GraphVertex* findNeighbor(const VertData &neighborData) {
        auto edge = m_edges;
        while (edge != nullptr) {
            if (edge->target()->data() == neighborData)
                return edge->target();
            edge = edge->next();
        }
        return nullptr;
    }

    GraphVertex* findNeighborByEdge(const EdgeData &edgeData) {
        auto edge = m_edges;
        while (edge != nullptr) {
            if (edge->data() == edgeData)
                return edge->target();
            edge = edge->next();
        }
        return nullptr;
    }


private:

    friend class Graph<VertData,EdgeData>;

    TEdge *m_edges;
    VertData m_data;
};


// Base class for graph classes
template <
    typename VertData,
    typename EdgeData=VertData
>
class Graph
{
public:

    typedef GraphEdge<VertData,EdgeData> TEdge;
    typedef GraphVertex<VertData,EdgeData> TVertex;

    Graph(MemoryPool *vertPool, MemoryPool *edgePool, const VertData &entryData)
        : m_vertPool(vertPool)
        , m_edgePool(edgePool)
    {
        m_entry = vertPool->alloc<TVertex>(entryData);
    }

    TVertex* entry() { return m_entry; }
    const TVertex* entry() const { return m_entry; }

    void addNeighbor(TVertex *vertex, const EdgeData &edgeData, const VertData &neighborData) {
        auto neighbor = m_vertPool->alloc<TVertex>(neighborData);
        auto edge = m_edgePool->alloc<TEdge>(vertex, neighbor, edgeData);
        // prepend to edge list
        edge->m_next = vertex->m_edges;
        vertex->m_edges = edge;
    }



private:

    MemoryPool *m_vertPool;
    MemoryPool *m_edgePool;
    TVertex *m_entry;
};


} // namespace Ksl

#endif // KSL_GRAPH_H
