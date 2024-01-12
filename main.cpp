#include "avltree.h"

int main() {

  std::vector<std::vector<int>> jimmy{// {9, 11, 17, 29, 4},
                                      // {9, 11, 17, 29, 7},
                                      {9, 20, 4, 21, 22, 23, 24}};

  try {
    for (auto itemlist : jimmy) {
      auto x = Tree();

      for (auto var : itemlist) {
        x.Insert(var);
      }
      std::cout << x.Dotify();
    }

  } catch (const std::invalid_argument &e) {
    fmt::println("exception: {}", e.what());
  }

  return -1;
}
