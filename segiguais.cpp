#include <bits/stdc++.h>

typedef struct Elemento
{
  int number;
  int quantity;

  Elemento(int number, int quantity)
  {
    this->number = number;
    this->quantity = quantity;
  }
} Elemento;

int main()
{
  std::string fileName;
  std::ifstream file;
  int n; // numero de elementos
  int previousElement, actualElement;

  std::cout << "Digite o nome do arquivo: ";
  std::cin >> fileName;

  file.open(fileName);
  file >> n;

  std::vector<Elemento> elements; // para guardar as repeticoes
  std::map<int, int> segmentsMap; // para guardar qual numero tem qual segmento
  std::set<int> values;

  file >> actualElement;
  previousElement = actualElement;
  values.insert(actualElement);

  int repeatCounter = 1;
  for (int i = 1; i < n; i++)
  {
    file >> actualElement;

    if (previousElement != actualElement)
    {
      elements.push_back(Elemento(previousElement, repeatCounter));

      repeatCounter = 1;
      if (values.find(actualElement) == values.end())
      {
        values.insert(actualElement);
      }
    }
    else
    {
      repeatCounter = repeatCounter + 1;
    }

    previousElement = actualElement;
  }
  elements.push_back(Elemento(previousElement, repeatCounter)); // o ultimo estava de fora

  std::string line1;
  std::string line2;
  std::cout << "Matriz:\n";
  for (auto e : elements)
  {
    auto it = values.find(e.number);
    int index = std::distance(values.begin(), it) + 1;
    
    line1.append(std::to_string(index) + " ");
    line2.append(std::to_string(e.quantity) + " ");
  }

  // removendo os ultimos espacos
  line1.pop_back();
  line2.pop_back();
  std::cout << line1 << "\n";
  std::cout << line2 << "\n";

  // gerando o segmento

  return 0;
}