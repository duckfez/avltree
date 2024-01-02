// avltree.cpp : Where Duane tries to build an AVL tree
//

#include "avltree.h"

using namespace std;

class TreeItem : public std::enable_shared_from_this<TreeItem> {
public:
  int value;
  shared_ptr<TreeItem> left;
  shared_ptr<TreeItem> right;

  TreeItem(int val) {
    value = val;
    left = nullptr;
    right = nullptr;
    // fmt::println("treeitem cdr value={}, left={}, right={}", value,
    // fmt::ptr(left), fmt::ptr(right));
  }

  void Insert(int val) {
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
  void Visit(std::function<void(shared_ptr<TreeItem const>)> funky) const {
    if (this->left != nullptr) {
      this->left->Visit(funky);
    }

    auto x = shared_from_this();
    funky(x);

    if (this->right != nullptr) {
      this->right->Visit(funky);
    }
  }
};

class Tree {
  shared_ptr<TreeItem> root;

public:
  Tree() {
    // fmt::println("in constructor");
    root = nullptr;
  }

  void Insert(int value) {
    if (this->root == nullptr) {
      this->root = make_shared<TreeItem>(value);
    } else {
      root->Insert(value);
    }
  }

  std::string Dotify(void) {
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

  std::string List(void) {
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
};

int main() {
  auto x = Tree();

  try {
    x.Insert(10);
    x.Insert(4);
    x.Insert(20);
    x.Insert(21);
    x.Insert(22);
    x.Insert(23);
    x.Insert(24);
    x.Insert(25);
  } catch (const std::invalid_argument &e) {
    fmt::println("exception: {}", e.what());
  }

  std::cout << x.Dotify();
  // std::cout << x.List();

  return 0;
}
