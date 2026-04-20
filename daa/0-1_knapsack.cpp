#include <cstdlib>
#include <iostream>

struct Item {
  int value;
  int weight;
};

int knapsack(Item items[], int count, int capacity)
{
  int *M = new int[(count+1)*(capacity+1)];

  for (int i = 0; i <= capacity; i++) {
    M[i] = 0;
  }

  for (int i = 1; i <= count; i++) {
    for (int j = 0; j <= capacity; j++) {
      if (items[i-1].weight > j) {
        M[i*(capacity+1) + j] = M[(i-1)*(capacity+1) + j];
        continue;
      }

      int include = M[(i-1)*(capacity+1) + (j - items[i-1].weight)] + items[i-1].value;
      int exclude = M[(i-1)*(capacity+1) + j];
      int max = (include > exclude) ? include : exclude;

      M[i*(capacity+1) + j] = max;
    }
  }

  return M[count*(1+capacity) + capacity];
}

int get_items(Item **out)
{
  int item_count;

  std::cout << "Enter number of items: ";
  std::cin >> item_count;

  if (item_count < 1) {
    std::cout << "Error: Number of items must be positive\n";
    std::exit(1);
  }

  Item *items = new Item[item_count];
  for (int i = 0; i < item_count; i++) {
    int weight, value;

    std::cout << "Item " << i+1 << ":\n";

    std::cout << "  Weight: ";
    std::cin >> weight;

    if (weight < 1) {
      std::cout << "Error: Weight must be positive\n";
      std::exit(1);
    }

    std::cout << "  Value: ";
    std::cin >> value;

    if (value < 1) {
      std::cout << "Error: Value must be positive\n";
      std::exit(1);
    }

    items[i].weight = weight;
    items[i].value = value;
  }

  *out = items;

  return item_count;
}

int main()
{
  Item *items;
  int item_count = get_items(&items);
  int result = knapsack(items, item_count, 6);
  
  std::cout << "Result: " << result << '\n';

  return 0;
}
