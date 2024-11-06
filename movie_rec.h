#ifndef movie_rec.h
#define movie_rec.h

#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <cmath>
#include <utility>

using namespace std;

class RecommenderSystem {
public:
    RecommenderSystem();

    // User-related functions
    void addUserInfo(int id, int item_id, double rating);
    void addtestInfo(int id, int item_id);

    // Prediction functions
    double IBCF(int item_id, int user_id);
    list<double> make_predictions();

    // Similarity and error functions
    double rmse(const list<double> &predictions, const list<double> &true_values);
    double cosine_similarity(const vector<double> &vec1, const vector<double> &vec2);
    double item_similarity(map<int, double> v1, map<int, double> v2);

    // Utility functions
    void printUser(int id);
    void printAllUsers();
    void printTestList();
    unsigned long size();
    void topUsers();
    void topItems();
    
    // Sorting helper
    void sortArray(int(&rate)[10], int(&id)[10]);

private:
    map<int, map<int, double>> userMap;
    list<pair<int, int>> testList;

    // Find minimum index in an array (template function must be defined in header)
    template<class type>
    int findmin_index(type array[], int size) {
        type min = array[0];
        int index = 0;
        for (int i = 1; i < size; i++) {
            if (array[i] < min) {
                min = array[i];
                index = i;
            }
        }
        return index;
    }
};

#endif // done
