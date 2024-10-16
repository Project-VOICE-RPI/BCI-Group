////////////////////////////////////////////////////////////////////////////////
// $Id: FilterGraph.cpp 8215 2024-06-21 13:36:37Z mellinger $
// Author: mellinger@neurotechcenter.org
// Description: Filter graph definitions.
//
// $BEGIN_BCI2000_LICENSE$
//
// This file is part of BCI2000, a platform for real-time bio-signal research.
// [ Copyright (C) 2000-2023: BCI2000 team and many external contributors ]
//
// BCI2000 is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// BCI2000 is distributed in the hope that it will be useful, but
//                         WITHOUT ANY WARRANTY
// - without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// this program.  If not, see <http://www.gnu.org/licenses/>.
//
// $END_BCI2000_LICENSE$
////////////////////////////////////////////////////////////////////////////////
#include "FilterGraph.h"
#include "FilterGraphNode.h"
#include "IndentingOStreambuf.h"
#include "SubchainFilter.h"
#include "PlaceholderNode.h"
#include "GraphSearch.h"

namespace FilterGraph
{

// Graph::iterator class
Graph::iterator::iterator() : graph(nullptr), index(0)
{
}

Graph::iterator::iterator(Graph *graph, size_t index) : graph(graph), index(index)
{
}

Graph::iterator::iterator(const iterator &i) : graph(i.graph), index(i.index)
{
}

Graph::iterator::operator void *() const
{
    return graph;
}

bool Graph::iterator::operator==(const iterator &other) const
{
    return graph == other.graph && index == other.index;
}

bool Graph::iterator::operator!=(const iterator &other) const
{
    return !(*this == other);
}

Node *Graph::iterator::operator*() const
{
    return graph->mNodes[index];
}

Graph::iterator &Graph::iterator::operator++()
{
    ++index;
    return *this;
}

Graph::iterator Graph::iterator::operator++(int)
{
    iterator i = *this;
    ++index;
    return i;
}

// Graph::const_iterator class
Graph::const_iterator::const_iterator() : graph(nullptr), index(0)
{
}

Graph::const_iterator::const_iterator(const Graph *graph, size_t index) : graph(graph), index(index)
{
}

Graph::const_iterator::const_iterator(const const_iterator &i) : graph(i.graph), index(i.index)
{
}

Graph::const_iterator::const_iterator(const iterator &i) : graph(i.graph), index(i.index)
{
}

Graph::const_iterator::operator const void *() const
{
    return graph;
}

bool Graph::const_iterator::operator==(const const_iterator &other) const
{
    return graph == other.graph && index == other.index;
}

bool Graph::const_iterator::operator!=(const const_iterator &other) const
{
    return !(*this == other);
}

const Node *Graph::const_iterator::operator*() const
{
    return graph->mNodes[index];
}

Graph::const_iterator &Graph::const_iterator::operator++()
{
    ++index;
    return *this;
}

Graph::const_iterator Graph::const_iterator::operator++(int)
{
    const_iterator i = *this;
    ++index;
    return i;
}

// Graph class
Graph::Graph(const std::string &name) : mName(name), mpFilter(nullptr)
{
    ::memset(&mPerformanceData, 0, sizeof(mPerformanceData));
}

Graph::Graph(const Graph &other)
{
    cloneFrom(other);
}

Graph &Graph::operator=(const Graph &other)
{
    cloneFrom(other);
    return *this;
}

Graph::~Graph()
{
    clear();
}

bool Graph::operator==(const Graph &other) const
{
    std::ostringstream oss1, oss2;
    this->serialize(oss1);
    other.serialize(oss2);
    return oss1.str() == oss2.str();
}

bool Graph::operator!=(const Graph &other) const
{
    return !operator==(other);
}

Graph::iterator Graph::begin()
{
    iterator i = {this, 0};
    return i;
}

Graph::iterator Graph::end()
{
    iterator i = {this, mNodes.size()};
    return i;
}

Graph::const_iterator Graph::begin() const
{
    const_iterator i = {this, 0};
    return i;
}

Graph::const_iterator Graph::end() const
{
    const_iterator i = {this, mNodes.size()};
    return i;
}

bool Graph::empty() const
{
    return mNodes.empty();
}

void Graph::clear()
{
    for (auto pNode : mNodes)
        delete pNode;
    mNodes.clear();
    mpFilter = nullptr;
}

void Graph::setName(const std::string &s)
{
    mName = s;
}

const std::string &Graph::name() const
{
    return mName;
}

void Graph::cloneFrom(const Graph &other)
{
    clear();
    for (size_t i = 0; i < other.mNodes.size(); ++i)
        mNodes.push_back(other.mNodes[i]->clone());
    mName = other.mName;
    mpFilter = other.mpFilter;
    mPerformanceData = other.mPerformanceData;
}

void Graph::erase(size_t pos)
{
    if (pos < mNodes.size())
        delete mNodes[pos];
    for (size_t i = pos + 1; i < mNodes.size(); ++i)
        mNodes[i - 1] = mNodes[i];
    if (pos < mNodes.size())
        mNodes.resize(mNodes.size() - 1);
}

void Graph::insert(size_t pos, Node *pNode)
{
    mNodes.resize(mNodes.size() + 1);
    for (size_t i = mNodes.size() - 1; i > pos; --i)
        mNodes[i] = mNodes[i - 1];
    mNodes[pos] = pNode;
}

void Graph::push_back(Node *pNode)
{
    mNodes.push_back(pNode);
}

struct Graph::Registrar : GenericFilter::FilterRegistrar<SubchainFilter>
{
    const Graph &mrGraph;

    Registrar(const Graph &graph, Directory::Node *pNode) : FilterRegistrar<SubchainFilter>(pNode), mrGraph(graph)
    {
    }

    GenericFilter *NewInstance() const override
    {
        GenericFilter *pFilter = FilterRegistrar<SubchainFilter>::NewInstance();
        SubchainFilter *pSubchain = dynamic_cast<SubchainFilter *>(pFilter);
        Assert(pSubchain);
        pSubchain->SetName(mrGraph.name());
        for (Graph::const_iterator i = mrGraph.begin(); i != mrGraph.end(); ++i)
        {
            auto p = (*i)->getRegistrar(pSubchain);
            if (p)
                pSubchain->Add(p);
        }
        mrGraph.mpFilter = pFilter;
        return pSubchain;
    }
};

GenericFilter::Registrar *Graph::getRegistrar(Directory::Node *pNode) const
{
    return new Graph::Registrar(*this, pNode);
}

GenericFilter *Graph::filterInstance() const
{
    return mpFilter;
}

GenericFilter *Graph::instantiateAsFilter(Directory::Node *pDirectoryNode) const
{
    if (!isRunnable())
        return nullptr;

    // pReg will be auto-deleted, so we may not delete it here.
    auto pReg = getRegistrar(pDirectoryNode);
    return pReg->NewInstance();
}

bool Graph::isRunnable() const
{
    if (empty())
        return false;
    return search<PlaceholderNode>(*this).empty();
}

const struct GenericFilter::PerformanceData &Graph::performanceData() const
{
    return mPerformanceData;
}

void Graph::gatherPerformanceData()
{
    if (mpFilter)
        mPerformanceData = mpFilter->PerformanceData();
    else
        ::memset(&mPerformanceData, 0, sizeof(mPerformanceData));
    for (auto i = begin(); i != end(); ++i)
        (*i)->gatherPerformanceData();
}

void Graph::clearFilterInstances()
{
    mpFilter = nullptr;
    for (auto i = begin(); i != end(); ++i)
        (*i)->clearFilterInstances();
}

void Graph::serialize(std::ostream &os) const
{
    if (!mName.empty())
        os << mName << "\n";
    os << "{\n";
    {
        IndentingOStreambuf indent(os, 2);
        for (size_t i = 0; i < mNodes.size(); ++i)
            mNodes[i]->serialize(os);
    }
    os << "}\n";
}

Graph Graph::unserialize(std::istream &is)
{
    Graph graph;
    std::string s;
    is >> s;
    if (s != "{")
    {
        graph.mName = s;
        is >> s;
    }
    if (s != "{")
        is.setstate(std::ios::failbit);
    is >> std::ws;
    while (is && is.peek() != '}')
    {
        Node *pNode = Node::unserialize(is);
        graph.push_back(pNode);
        is >> std::ws;
    }
    is >> s;
    if (s != "}")
        is.setstate(std::ios::failbit);
    return graph;
}

} // namespace FilterGraph
