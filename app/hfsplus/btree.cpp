#include "btree.h"
#include "hfs_file.h"

#include <cassert>

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
BTree::BTree(HFSFile* file)
  : m_file(file)
{
  auto b0 = m_file->read_block(0);
  BTNodeDescriptor btnode;
  btnode.read_from(b0);
  assert(btnode.kind == kBTHeaderNode);

  // TODO here
  auto header = ;
}

bool BTree::node_in_use(uint32_t no)
{
  return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
