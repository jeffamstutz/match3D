// Copyright 2021 Jefferson Amstutz
// SPDX-License-Identifier: Apache-2.0

#include "NodeGraph.h"
// std
#include <algorithm>

static int g_nextID{0};

Port::Port(std::string name, const Node *node)
    : m_name(name), m_node(node), m_id(g_nextID++)
{}

const char *Port::name() const
{
  return m_name.c_str();
}

const Node *Port::node() const
{
  return m_node;
}

int Port::id() const
{
  return m_id;
}

Node::Node(const char *n) : m_name(n), m_id(g_nextID++) {}

const char *Node::name() const
{
  return m_name.c_str();
}

int Node::id() const
{
  return m_id;
}

const OutPortArray &Node::outgoing() const
{
  return m_outgoing;
}

const InPortArray &Node::incoming() const
{
  return m_incoming;
}

Link::Link() : m_id(g_nextID++) {}

const int Link::id() const
{
  return m_id;
}

void NodeGraph::addNode(NodePtr node)
{
  m_nodes.push_back(std::move(node));
}

void NodeGraph::removeNode(int id)
{
  m_links.erase(std::remove_if(m_links.begin(),
                    m_links.end(),
                    [&](const auto &link) -> bool {
                      return link.to->node()->id() == id
                          || link.from->node()->id() == id;
                    }),
      m_links.end());

  m_nodes.erase(std::remove_if(m_nodes.begin(),
                    m_nodes.end(),
                    [&](const auto &node) -> bool { return node->id() == id; }),
      m_nodes.end());
}

int NodeGraph::addLink(int fromPortID, int toPortID)
{
  Link link;

  std::find_if(m_nodes.begin(), m_nodes.end(), [&](auto &n) {
    for (auto &ip : n->outgoing()) {
      if (ip.id() == fromPortID) {
        link.from = &ip;
        return true;
      }
    }
    return false;
  });

  std::find_if(m_nodes.begin(), m_nodes.end(), [&](auto &n) {
    for (auto &op : n->incoming()) {
      if (op.id() == toPortID) {
        link.to = &op;
        return true;
      }
    }
    return false;
  });

  if (link.from == nullptr) {
    printf("BAD LINK CREATED: 'from' is nullptr (ids: %i, %i)\n",
        fromPortID,
        toPortID);
    fflush(stdout);
    std::terminate();
  }

  if (link.to == nullptr) {
    printf("BAD LINK CREATED: 'to' is nullptr (ids: %i, %i)\n",
        fromPortID,
        toPortID);
    fflush(stdout);
    std::terminate();
  }

  m_links.push_back(link);
  return m_links.back().id();
}

void NodeGraph::removeLink(int id)
{
  m_links.erase(std::remove_if(m_links.begin(),
                    m_links.end(),
                    [&](const auto &link) -> bool { return link.id() == id; }),
      m_links.end());
}

const NodeArray &NodeGraph::nodes() const
{
  return m_nodes;
}

const LinkArray &NodeGraph::links() const
{
  return m_links;
}
