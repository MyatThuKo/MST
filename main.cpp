#include<iostream>
#include<string>
#include<sstream>
#include<fstream>

using namespace std;

bool isConnected (int tree[100][100], int index) {

  for (int i = 0; i < 100; i++) {
    if (tree[index][i] != 0) {
      return true;
    }
  }
  return false;
}

int isMinIndex (int key[], bool isIncluded[], int count) {

  int min = INT_MAX, minIndex;

  for (int i = 0; i < count; i++) {
    if (isIncluded[i] == false && key[i] < min) {
      min = key[i];
      minIndex = i;
    }
  }
  return minIndex;
}

void minTree (int tree[100][100]) {

  int isValid[100] = {};

  for (int i = 0; i < 100; i++) {
    isValid[i] = -1;
  }

  int count = 0;

  for (int i = 0; i < 100; i++) {
    if (isConnected(tree, i) == true) {
      isValid[count] = i;
      count++;
    }
  }

  int key[count];

  bool isIncluded[count];

  for (int i = 0; i < count; i++) {
    key[i] = INT_MAX;
    isIncluded[i] = false;
  }

  key[0] = 0;

  int parent[count];

  parent[0] = -1;

  int indexOne, indexTwo;

  for (int i = 0; i < count; i++) {
    int minIndex = isMinIndex(key, isIncluded, count);

    isIncluded[minIndex] = true;

    indexOne = isValid[minIndex];

    for (int j = 0; j < count; j++) {
      indexTwo = isValid[j];
      if (tree[indexOne][indexTwo] != 0 && isIncluded[indexTwo] == false && tree[indexOne][indexTwo] < key[j]) {
        key[j] = tree[indexOne][indexTwo];
        parent[j] = minIndex;
      }
    }
  }

  int total = 0;

  ofstream myfile;
  myfile.open ("output.txt");
  myfile << "Save the Minimum Spanning Tree in the text file. " << endl;

  // This is for the program cout.
  cout << "Minimum Spanning Tree: " << endl;

  for (int x = 1; x < count; x++) {
    cout << isValid[parent[x]]	<< " " << isValid[x] << " " << tree[isValid[x]][isValid[parent[x]]] << endl;

    total += tree[isValid[x]][isValid[parent[x]]];
  }

  // This is for text file cout.
  myfile << "Minimum Spanning Tree: " << endl;
  for (int y = 1; y < count; y++) {
    myfile << isValid[parent[y]]	<< " " << isValid[y] << " " << tree[isValid[y]][isValid[parent[y]]] << endl;
  }

  cout << "Total Edge Weight: " << total << endl;
  myfile << "Total Edge Weight: " << total << endl;

  myfile.close();

  cin.get();
}

int main() {

  cout << "The program will read the edges and weight of the tree from a input.txt file." << endl;
  cout << "The program will be run automatically since \'end-of-file\' line is included in the input.txt file. " << endl;
  cout << "The output will be saved as \'output.txt\' file. " << endl;
  cout << "Please enter \'end\' to exit the program." << endl;

  int tree[100][100] = {};

  string menu;
  string input;

  int vertex1, vertex2, weight;

  cout << "This is the tree in the input.txt file." << endl;
  string STRING;
	ifstream infile;
	infile.open ("input.txt");
  while(!infile.eof()) {
    getline(infile, STRING);
    cout << STRING << endl;
    if (STRING == "end-of-file") {
    break;
  }
  istringstream stream(STRING);

  stream >> vertex1 >> vertex2 >> weight;

  tree[vertex1][vertex2] = weight;
  tree[vertex2][vertex1] = weight;
}
  minTree(tree);
	infile.close();

  return 0;

}
