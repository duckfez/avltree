// avltree.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include "fmt/core.h"
#include "fmt/format.h"
#include <functional>
#include <iostream>
#include <sstream>

// TODO: Reference additional headers your program requires here.

using namespace std;

class TreeItem : public std::enable_shared_from_this<TreeItem> {
public:
  int value;
  shared_ptr<TreeItem> left;
  shared_ptr<TreeItem> right;

  TreeItem(int val);
  void Insert(int val);
  void Visit(std::function<void(shared_ptr<TreeItem const>)> funky) const;
};

class Tree {
  shared_ptr<TreeItem> root;

public:
  Tree();
  void Insert(int value);
  std::string Dotify(void);
  std::string List(void);
};
