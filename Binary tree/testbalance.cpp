#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iomanip>
#include "bintree.cpp"
using namespace std;

double getAverage(vector<int> const& v){
    double sum{0.0};
    
    for(int i = 0; i < v.size(); i++){
        sum += v[i];
    }
    return sum/v.size();
}

double getAverageHeight(vector<int> const& a, vector<int> const& b){
    std::vector<int> averageHeightVec(a.size());
    if(a.size() == b.size()){
        for(int i = 0; i < a.size(); i++){
            averageHeightVec[i] = (a[i]+b[i])/2;
        }
    }
    return getAverage(averageHeightVec);
}


vector<int> getDifference(vector<int> const& a, vector<int> const& b){
    std::vector<int> diffVec(a.size());
    if(a.size() == b.size()){
        for(int i = 0; i < a.size(); i++){
            diffVec[i] = abs(a[i]-b[i]);
        }
    }
    return diffVec;
}

void testBalance(int const& seed){
    std::cout << "Test balance binary tree" << std::endl;
    std::vector<int> elementVec(9000);
    std::vector<int> maxHeightVec(800);
    std::vector<int> minHeightVec(800);
    std::vector<int> sizeHeightVec(800);
    
    for(int i = 0; i < 9000; i++){
        elementVec[i] = i+1;
    }
    
    shuffle(elementVec.begin(), elementVec.end(), std::default_random_engine(seed)); //Seed for 001110
    
    for(int i = 0; i < 800; i++){
        Node *bintree = nullptr;
        
        for(int j = 0; j < 9000; j++){
            insert(bintree, elementVec[j], elementVec[j]);
        }

        next_permutation(elementVec.begin(), elementVec.end());
                
        maxHeightVec[i] = max_height(bintree);
        minHeightVec[i] = min_height(bintree);
        sizeHeightVec[i] = size(bintree);
        delete_tree(bintree);
    }

    auto maxHeight = max_element(begin(maxHeightVec), end(maxHeightVec));
    auto minHeight = min_element(begin(minHeightVec), end(minHeightVec));
  
    cout << fixed;
    cout << setprecision(2);
    cout << "Average height: " << getAverageHeight(minHeightVec,maxHeightVec) << endl;
    cout << "Highest maximum height: " << maxHeight[0] << endl;
    cout << "Average minimum height: " << getAverage(minHeightVec) << endl;
    cout << "Lowest minimum height: " << minHeight[0] << endl;
    
    auto diffHeight = getDifference(minHeightVec,maxHeightVec);
    auto maxDiffHeight = max_element(begin(diffHeight), end(diffHeight));
    auto minDiffHeight = min_element(begin(diffHeight), end(diffHeight));

    cout << "Average difference between heights: " << getAverage(diffHeight) << endl;
    cout << "The greatest difference between minimum and maximum height: " << maxDiffHeight[0] << endl;
    cout << "The lowest difference between minimum and maximum height: " << minDiffHeight[0] << endl;
}

void improvedTest(int const& seed){
    std::cout << "Improved test balance binary tree" << std::endl;
    std::vector<int> elementVec(9000);
    std::vector<int> maxHeightVec(800);
    std::vector<int> minHeightVec(800);
    std::vector<int> sizeHeightVec(800);
    
    srand(seed);
    for(int i = 0; i < 800; i++){
        Node *bintree = nullptr;
        
        //create a randomly sized dataset
        int randomDatasetSize = rand() % 9000;
        vector<int> elementVec(randomDatasetSize); //Testing with different sizes to shorten the running time
        for(int i = 0; i < randomDatasetSize; i++){
            elementVec[i] = i+1;
        }

        shuffle(elementVec.begin(), elementVec.end(), std::default_random_engine(seed));
        
        for(int i = 0; i < randomDatasetSize; i++){
            insert(bintree, elementVec[i], elementVec[i]);
        }
        
        maxHeightVec[i] = max_height(bintree);
        minHeightVec[i] = min_height(bintree);
        sizeHeightVec[i] = size(bintree);
        delete_tree(bintree);
    }

    auto maxHeight = max_element(begin(maxHeightVec), end(maxHeightVec));
    auto minHeight = min_element(begin(minHeightVec), end(minHeightVec));
  
    cout << fixed;
    cout << setprecision(2);
    cout << "Average height: " << getAverageHeight(minHeightVec,maxHeightVec) << endl;
    cout << "Highest maximum height: " << maxHeight[0] << endl;
    cout << "Average minimum height: " << getAverage(minHeightVec) << endl;
    cout << "Lowest minimum height: " << minHeight[0] << endl;
    
    auto diffHeight = getDifference(minHeightVec,maxHeightVec);
    auto maxDiffHeight = max_element(begin(diffHeight), end(diffHeight));
    auto minDiffHeight = min_element(begin(diffHeight), end(diffHeight));

    cout << "Average difference between heights: " << getAverage(diffHeight) << endl;
    cout << "The greatest difference between minimum and maximum height: " << maxDiffHeight[0] << endl;
    cout << "The lowest difference between minimum and maximum height: " << minDiffHeight[0] << endl;

}

int main(int argc, const char * argv[]) {
    //Seed is 001110 -> 1110
    testBalance(1110);
    std::cout << "-------------------------------------------------------------------" <<endl;
    improvedTest(1110);
    return 0;
}