// avltree.cpp : Where Duane tries to build an AVL tree
//

#include "avltree.h"

using namespace std;

TreeItem::TreeItem(int val) {
  value = val;
  left = nullptr;
  right = nullptr;
  // fmt::println("treeitem cdr value={}, left={}, right={}", value,
  // fmt::ptr(left), fmt::ptr(right));
}

void TreeItem::Insert(int val) {
  if (val < this->value) {
    if (this->left == nullptr) {
      this->left = make_shared<TreeItem>(val);
    } else {
      this->left->Insert(val);
    }
  } else if (val > this->value) {
    if (this->right == nullptr) {
      this->right = make_shared<TreeItem>(val);
    } else {
      this->right->Insert(val);
    }
  } else {
    throw std::invalid_argument("duplicate value");
  }
}

// Visits every item in the tree, calling the function
// with the visited item as an argument
// for the record this is an inorder traversal
void TreeItem::Visit(
    std::function<void(shared_ptr<TreeItem const>)> funky) const {
  if (this->left != nullptr) {
    this->left->Visit(funky);
  }

  auto x = shared_from_this();
  funky(x);

  if (this->right != nullptr) {
    this->right->Visit(funky);
  }
}

Tree::Tree() {
  // fmt::println("in constructor");
  root = nullptr;
}

void Tree::Insert(int value) {
  if (this->root == nullptr) {
    this->root = make_shared<TreeItem>(value);
  } else {
    root->Insert(value);
  }
}

std::string Tree::Dotify(void) {
  std::ostringstream oss;
  int nullcount = 0;

  auto pot = [=, &oss, &nullcount](shared_ptr<TreeItem const> item) {
    if (item->left != nullptr) {
      oss << fmt::format("{} -> {};", item->value, item->left->value)
          << std::endl;
    } else {
      auto nullid = fmt::format("null{}", nullcount++);
      oss << fmt::format("{} -> {};", item->value, nullid) << std::endl;
      oss << fmt::format("{}[label = \"null\"]", nullid) << std::endl;
    }

    if (item->right != nullptr) {
      oss << fmt::format("{} -> {};", item->value, item->right->value)
          << std::endl;
    } else {
      auto nullid = fmt::format("null{}", nullcount++);
      oss << fmt::format("{} -> {};", item->value, nullid) << std::endl;
      oss << fmt::format("{}[label = \"null\"]", nullid) << std::endl;
    }
  };

  oss << "digraph {" << std::endl;

  if (this->root != nullptr) {
    this->root->Visit(pot);
  }

  oss << "}" << std::endl;
  return oss.str();
}

std::string Tree::List(void) {
  std::ostringstream oss;

  bool first = true;

  auto pot = [&oss, &first](shared_ptr<TreeItem const> item) {
    if (first == false)
      oss << ", ";
    oss << item->value;
    first = false;
  };

  if (this->root != nullptr) {
    this->root->Visit(pot);
  }

  return oss.str();
}
