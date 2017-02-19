#include <iostream>

using namespace std;

double matrixAugmented[1005][1005];

void swapRow(int rowA, int rowB, int colSize){ //operasi baris elementer
  for(int c = 0; c < colSize; c++)
    swap(matrixAugmented[rowA][c], matrixAugmented[rowB][c]);
}

void multiplyRowElements(int row, double multiplier, int colSize){ //operasi baris elementer
  for(int c = 0;c < colSize; c++)
    matrixAugmented[row][c] *= multiplier;
}

void rowAdditionWithMultipliedRowElements(int rowSource, int rowTarget, double multiplier, int colSize){ //operasi baris elementer
  for(int c = 0; c < colSize; c++)
    matrixAugmented[rowTarget][c] += (matrixAugmented[rowSource][c] * multiplier);
}

int firstElementMustBeOne(int currentRow, int currentCol, int rowSize, int colSize){ // return currentCollumn
  for (int c = currentCol; c < colSize - 1; c++){
    for (int r = currentRow; r < rowSize; r++){
      if (matrixAugmented[r][c] != 0.0){
        multiplyRowElements(r, 1.0/(double)matrixAugmented[r][c], colSize);
        swapRow(r, currentRow, colSize);
        return c;
      }
    }
  }
  return colSize-1;
}

void gaussJordan(int rowSize, int colSize){
  int c = 0, r = 0;
  while(c < colSize - 1 &&  r < rowSize){
    c = firstElementMustBeOne(r, c, rowSize, colSize);
    for(int i=r+1; i<rowSize; i++){
      if(matrixAugmented[i][c] != 0.0) //dilarang dibagi dengan nol !!!
        rowAdditionWithMultipliedRowElements(r, i, (-1.0 * matrixAugmented[i][c]), colSize);
    }
    r++;
    c++;
  }
  int k;
  for(int b=rowSize-1; b>=0; b--){
    for(k=0; k<colSize-1; k++){
      if(matrixAugmented[b][k]==1.0) //satu utama
        break;
    }
    if (k<colSize-1){
      for(int i=b-1; i>=0; i--)
        rowAdditionWithMultipliedRowElements(b, i, (-1.0 * matrixAugmented[i][k]), colSize);
    }
  }
}

void printMatrix(int rowSize, int colSize){
  for(int r=0; r<rowSize; r++){
    for(int c=0; c<colSize; c++)
      cout << matrixAugmented[r][c] << " \t";
    cout << "\n";
  }
  cout << endl;
}

int main(){
  int row, col;
  cout << "Input ukuran matriks augmented (baris kolom) tanpa tanda ( ) : ";
  cin >> row >> col;
  cout << "Input matriks augmented :" << endl;
  for (int r = 0; r < row; r++)
    for(int c = 0; c < col; c++)
      cin >> matrixAugmented[r][c];
  string cmd;
  double args[3];
  gaussJordan(row, col);
  printMatrix(row, col);
}
