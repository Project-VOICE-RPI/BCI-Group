////////////////////////////////////////////////////////////////////////////////
// $Id: StaticNodes.cpp 7463 2023-06-30 14:59:17Z mellinger $
// Author: mellinger@neurotechcenter.org
// Description: Nodes that cannot be removed or edited.
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
#include "StaticNodes.h"

namespace FilterGraph
{

StaticNode::StaticNode(const std::string &s) : Node(s)
{
}

void StaticNode::onSerialize(std::ostream &os) const
{
    os << type() << "\n";
}

std::string SourceNode::sType = Node::registerType("SourceNode", &SourceNode::create);

SourceNode::SourceNode() : StaticNode("Source")
{
}

Node *SourceNode::clone() const
{
    return create();
}

Node *SourceNode::create()
{
    return new SourceNode;
}

const std::string &SourceNode::type() const
{
    return sType;
}

} // namespace FilterGraph
