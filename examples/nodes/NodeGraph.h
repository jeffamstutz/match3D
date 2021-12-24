// Copyright 2021 Jefferson Amstutz
// SPDX-License-Identifier: Apache-2.0

// std
#include <memory>
#include <string>
#include <vector>

struct Node;

struct Port
{
  Port(std::string name, const Node *node);

  const char *name() const;
  const Node *node() const;
  int id() const;

 private:
  std::string m_name;
  const Node *m_node;
  int m_id{-1};
};

using OutPort = Port;
using InPort = Port;
using OutPortArray = std::vector<OutPort>;
using InPortArray = std::vector<InPort>;

struct Node
{
  Node(const char *name);

  const char *name() const;
  int id() const;

  const OutPortArray &outgoing() const;
  const InPortArray &incoming() const;

 protected:
  std::vector<OutPort> m_outgoing;
  std::vector<InPort> m_incoming;

 private:
  std::string m_name;
  int m_id{-1};
};

using NodePtr = std::unique_ptr<Node>;
using NodeArray = std::vector<NodePtr>;

template <typename T, typename... Args>
inline NodePtr make_Node(Args &&...args)
{
  return NodePtr(new T(std::forward<Args>(args)...));
}

struct Link
{
  Link();

  const OutPort *from{nullptr};
  const InPort *to{nullptr};

  const int id() const;

 private:
  int m_id{-1};
};

using LinkArray = std::vector<Link>;

struct NodeGraph
{
  NodeGraph() = default;

  void addNode(NodePtr node);
  void removeNode(int id);

  int addLink(int fromPortID, int toPortID);
  void removeLink(int id);

  const NodeArray &nodes() const;
  const LinkArray &links() const;

 private:
  NodeArray m_nodes;
  LinkArray m_links;
};
