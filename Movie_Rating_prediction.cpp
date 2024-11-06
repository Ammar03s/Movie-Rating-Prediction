#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cctype>
#include "MOVIE_REC_H"

using namespace std;

struct movie_ranking {
    int item_id;
    float rate;
};

unordered_map<int, unordered_map<int, float>> ranking;
unordered_map<int, vector<int>> watched_list;
unordered_map<int, string> movie_guide;
unordered_map<int, float> average_users_rating;
unordered_map<int, vector<movie_ranking>> collection;

bool evaluate_movies(const movie_ranking& lhs, const movie_ranking& rhs) {
    return lhs.rate > rhs.rate;
}

int str_to_int(const string& str) {
    if (str.empty() || !all_of(str.begin(), str.end(), ::isdigit)) {
        throw invalid_argument("Invalid integer string: " + str);
    }
    return stoi(str);
}


bool read_users_rating(const string &fileName) {
    // Open the file to R
    fstream trainFile(fileName, ios::in);

    // Check if the file successfly opened
    if (!trainFile.is_open()) {
        return false;
    }

    // Read data from the file
    string line;
    while (getline(trainFile, line)) {
        stringstream ss(line);
        string UserID_str, ItemID_str, Rating_str;

        getline(ss, UserID_str, ',');
        getline(ss, ItemID_str, ',');
        getline(ss, Rating_str, ',');


        try {
            int UserID = str_to_int(UserID_str);
            int ItemID = str_to_int(ItemID_str);
            float Rating = stof(Rating_str);

            ranking[UserID][ItemID] = Rating;
            watched_list[ItemID].push_back(UserID);

        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            // handle the error here (skipin this line and continue reading the file)
            continue;
        } catch (const std::out_of_range& e) {
            std::cerr << "Errorrrr: " << e.what() << std::endl;
            // handle the error here (skiping this line and continue reading the file)
            continue;
        }
    }

    // Close the file
    trainFile.close();
    return true;
}

// Func that calculates the avg rating for each user in a collection of the ratings
void rating_average() {
    for (auto & user_it : ranking) {
        float sum = 0;
        int count = 0;
        for (auto & user_movie : user_it.second) {
            sum += user_movie.second;
            ++count;
        }
        // Calc the avg rating and store it in the avg_rating container
        average_users_rating[user_it.first] = sum / count;
    }
}

// Func that uses cosine similarity formula to calc the similarity between the ratings given by the active user and the ratings given by each other user
unordered_map<int, float> get_similarity(int particular_user) {
    unordered_map<int, float> sim_map;
    
    const auto& particular_user_rating = ranking.at(particular_user);
    
    for (const auto& user_it : ranking) {
        int UserID = user_it.first;
        if (UserID == particular_user) continue;

        float dot_product = 0;
        float norm_active = 0;
        float norm_other = 0;

        for (const auto& [ItemID, rating] : particular_user_rating) {
            if (user_it.second.count(ItemID) == 0) continue;

            dot_product += rating * user_it.second.at(ItemID);
            norm_active += std::pow(rating, 2);
            norm_other += std::pow(user_it.second.at(ItemID), 2);
        }

        float denominator = std::sqrt(norm_active) * std::sqrt(norm_other);
        if (denominator != 0) sim_map[UserID] = dot_product / denominator;
    }

    return sim_map;
}

void movie_recommendation(int active_user, int K) {
    vector<movie_ranking>* predicted_rating = nullptr;
    bool needs_cleanup = false; //imp

    if (collection.find(active_user) == collection.end()) {
        unordered_map<int, float> corr_active = get_similarity(active_user);
        predicted_rating = new vector<movie_ranking>();
        needs_cleanup = true; //needs

         for (auto& movie_it : movie_guide) {
            int ItemID = movie_it.first;
            float pred_rating = 0;

            if (watched_list.find(ItemID) != watched_list.end()) {
                vector<int>& user_list = watched_list[ItemID];
                
                for (int UserID : user_list) {
                    if (corr_active.find(UserID) == corr_active.end()) continue;
                    pred_rating += corr_active[UserID] * (ranking[UserID][ItemID] - average_users_rating[UserID]);
                }
            }

            movie_ranking m;
            m.item_id = ItemID;
            m.rate = pred_rating;
            predicted_rating->push_back(m);
             
        }

        sort(predicted_rating->begin(), predicted_rating->end(), evaluate_movies);
        collection[active_user] = *predicted_rating;
        corr_active.clear();
    } else {
        predicted_rating = &collection[active_user];
    }

    cout << "\n" << K << " recommended movies for user : " << active_user << "\n";
    for (int i = 0; i < K && i < predicted_rating->size(); ++i) {
        cout << movie_guide[predicted_rating->at(i).item_id] << "\n";
    }

    if (needs_cleanup) {
        delete predicted_rating; //to clean up the memmory
    }
}


void clear_all() {
    average_users_rating.clear();
    movie_guide.clear();
    ranking.clear();
    watched_list.clear();
    collection.clear();
}

int main(int argc, char **argv) {
    bool isReadFileOk;
    string testFile, typeOk, trainFile;

    isReadFileOk = false;
    while (!isReadFileOk) {
        cout << "pls type the test file:\n";
        getline(cin, testFile);
        cout << "Your test file is:- " << testFile << "? Is that correct? \n [Y- Yes| N- No]";
        getline(cin, typeOk);
        isReadFileOk = typeOk == "Y" || typeOk == "y";
    }

    isReadFileOk = false;
    while (!isReadFileOk) {
        cout << "please type the train file: \n";
        getline(cin, trainFile);
        cout << "ur train file is: " << trainFile << "? Is that correct? \n [Y- Yes| N- No]";
        getline(cin, typeOk);
        isReadFileOk = typeOk == "Y" || typeOk == "y";
    }

    cout << "Okay then..\nStarting with files:\n"
            "Test file: \"" << testFile << "\"\n"
            "Train file: \"" << trainFile << "\"\n";

    cout << "Reading file \"" << testFile << "\" ....\n";

    fstream testFileStream(testFile, ios::in);
    if (!testFileStream.is_open()) {
        cout << testFile << " not possible to open!! pls make sure that it is present/readable!\n";
        return 1;
    }

    string line;
    while (getline(testFileStream, line)) {
        stringstream ss(line);
        string ID, UserID, ItemID;

        getline(ss, ID, ',');
        getline(ss, UserID, ',');
        getline(ss, ItemID, ',');

        try {
            int NUMBER_ID = str_to_int(ID);
            movie_guide[NUMBER_ID] = UserID + ItemID;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            continue;
        }
    }
    //choose the file g
    testFileStream.close();

    cout << "Reading file \"" << trainFile << "\" ...\n";
    if (read_users_rating(trainFile)) {
        cout << "computing User avg rating.. \n";
        rating_average();

        for (const auto& [user, _] : ranking) {
            int K = 10;
            cout << "recommendations for Mr.user " << user << ":\n";
            movie_recommendation(user, K);
            cout << "\n";
        }
        return 0;
    }

    return 1;
}

//end
