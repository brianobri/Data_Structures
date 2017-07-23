#ifndef SORTER_HPP
#define SORTER_HPP

#include <vector>
#include <queue>

// A class for sorting!
// You will finish this for project 4
// Yay
// All of the sorts will take a std::vector<int> and return a sorted std::vector<int>

struct Sorter {

  // sort a vector using bubble sort
  static std::vector<int> bubblesort(const std::vector<int>&);

  // sort a vector using insertion sort
  static std::vector<int> insertionsort(const std::vector<int>&);

  // sort a vector using radix sort
  static std::vector<int> radixsort(const std::vector<int>&);

  // sort a vector using quicksort
  static std::vector<int> quicksort(const std::vector<int>&);

  // sort a vector using mergesort
  static std::vector<int> mergesort(const std::vector<int>&);



};

int part(std::vector<int>& , int , int , int );
void qsort(std::vector<int>& , int , int );
void merges(std::vector<int>& , std::vector<int>& , int, int);
bool prior(int, int);

std::vector<int> Sorter::bubblesort(const std::vector<int>& vec) {
  // you need to change this
std::vector<int> tempVector;
tempVector = vec; // dont want to change init vector so made temp variable to return
int temp;
int vecSize = tempVector.size() - 1;
    for(int x = 0; x <= vecSize; x++)// first for loop traverses the list up to vecsize times
    {

        for(int y = vecSize; y > x; y--) // second for loop is for swapping if out of order down at position x the next smallest value, creating a sorted sublist of size x
        {
            if (tempVector[y] < tempVector[y-1])
            {
                std::swap(tempVector[y], tempVector[y-1]);
            }

        }

    }
return tempVector;
}

std::vector<int> Sorter::insertionsort(const std::vector<int>& vec) {
// you need to change this

std::vector<int> tempVector;
tempVector = vec; // dont want to change init vector so made temp variable to return
int vecSize = tempVector.size();

    for (int a = 1; a < vecSize; a++) // first loop finds position
    {
        for(int b = a;((b > 0) && (tempVector[b] < tempVector[b-1])); b--) // loops till sublist is in order then first loop moves a position
        {
            std::swap(tempVector[b], tempVector[b - 1]);
        }
    }
return tempVector;
}

std::vector<int> Sorter::radixsort(const std::vector<int>& vec) {

  // our main queue that will be turned into a vector at the end
  // also temporary storage as we move along the digits
  std::queue<int> main_queue;

  // see if the vector is empty
  if (vec.size() > 0) {

    // fill our main queue with the numbers in the vector
    // also find the largest value in the vector
    int largest = vec[0];
    for (int i = 0; i < vec.size(); ++i) {
      main_queue.push(vec[i]);
      largest = largest < vec[i] ? vec[i] : largest;
    }

    // compute the number of digits in the largest value
    int digits = 0;
    do {
      largest /= 10;
      ++digits;
    } while (largest != 0);

    // we need an array of queues for our buckets
    std::queue<int> buckets[10];

    //set a variable to hold the denominator
    int den = 1;

    // evaluate each digit for each number in the main_queue and put them
    // in the correct bucket for that digit's value
    for (int i = 0; i < digits; ++i) {
      // while the main queue has elements in it
      while(main_queue.size() > 0) {
	// store the number for storage later
	int temp = main_queue.front();
	main_queue.pop();
	// store the temp in the correct bucket
	buckets[(temp / den) % 10].push(temp);
      }

      // for each bucket
      for (int j = 0; j < 10; ++j) {
	// while there is something in the bucket
	while (buckets[j].size() > 0) {
	  // enqueue the value into our main queue
	  main_queue.push(buckets[j].front());
	  buckets[j].pop();
	}
      }

      // adjust the denominator for digit lookup later
      den *= 10;
    }
  }

  // move the sorted main queue into the return vector
  std::vector<int> ret;
  while(main_queue.size() > 0) {
    ret.push_back(main_queue.front());
    main_queue.pop();
  }
  return ret;
}

std::vector<int> Sorter::quicksort(const std::vector<int>& vec) {
  // you need to change this
    std::vector<int> tempVector;
    tempVector = vec; // dont want to change init vector so made temp variable to return
    qsort(tempVector, 0, vec.size()-1);

    return tempVector;
}

std::vector<int> Sorter::mergesort(const std::vector<int>& vec) {
  // you need to change this
  std::vector<int> tempVector,emptyvector;
  tempVector = emptyvector = vec; // dont want to change init vector so made temp variable to return
  merges(tempVector, emptyvector, 0, tempVector.size() - 1);
  return tempVector;
}


int part(std::vector<int>& data, int i, int j, int piv)
{
    do
    {
        while(prior(data[++i], piv)); // move positions from left and right until its the position to move
        while((i < j) && (prior(piv, data[--j])));
        std::swap(data[i], data[j]);
    }
    while(i < j); // stop when positions cross
    return i;

}

bool prior(int data1, int data2)
{
    if (data1 < data2)
    {
        return true;
    }
    else
    {
        return false;
    }
}


void qsort(std::vector<int> & data, int i, int j)
{
    if (j <= i)
    {
        return;
    }
    int pivpoint = (i + j) / 2;

    int z = data[j];
    int x = part(data, i - 1, j, z);
    std::swap(data[x], data[j]);
    qsort(data, i, x - 1); //left sublist
    qsort(data, x + 1, j);// right

}

void merges(std::vector<int>& mergesortvec, std::vector<int>& temp, int left, int right)
{
    if (left >= right)
    {
        return;
    }
    int middle = (left + right) / 2;
    merges(mergesortvec, temp, left, middle); // the divide part all the way down to size of 1
    merges(mergesortvec, temp, middle+1, right);
    for(int i = left; i <= right; i++) // the conquer part sort and merge
    {
        temp[i] = mergesortvec[i];
    }

        int x1 = left;
        int x2 = middle + 1;

        for (int y = left; y <=right; y++)
        {
            if (x1 == middle + 1)
            {
                mergesortvec[y] = temp[x2++];
            }
            else if(x2 > right)
            {
                mergesortvec[y] = temp[x1++];
            }
            else if(temp[x1] < temp[x2])
            {
                mergesortvec[y] = temp[x1++];
            }
            else
            {
                mergesortvec[y] = temp[x2++];
            }
        }




}

#endif
