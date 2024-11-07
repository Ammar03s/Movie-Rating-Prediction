# Movie Recommendation System

C++ based movie recommendation system that recommends movies to users based on collaborative filtering.


## Features
- Calculates average user ratings
- Computes user similarity using cosine similarity
- Generates movie recommendations for each user based on their similarity to other users
- Supports clearing data structures and restarting the recommendation process

## Usage
1. Compile the code using a C++ compiler:
   ```
   g++ -o movie_recommender main.cpp
   ```
2. Run the program and provide the paths to the training and test files when prompted.
3. The program will output the top 10 recommended movies for each user.

## Data Files
The program expects two data files:
1. **Training File**: Contains movie rating data in the format `user_id,item_id,rating`.
2. **Test File**: Contains user and movie information in the format `id,user_id,item_id`.

## Algorithms
The recommender system uses the following algorithms:
1. **Average User Rating**: Calculates the average rating for each user.
2. **User Similarity**: Computes the cosine similarity between the active user's ratings and other users' ratings.
3. **Predicted Rating**: Calculates the predicted rating for a movie as the sum of the active user's similarity to other users multiplied by the difference between the other user's rating and their average rating.
4. **Recommendation**: Recommends the top 'K' movies with the highest predicted ratings to the active user.



## Example Output

```
10 recommended movies for user: 12345
Movie 1
Movie 2
...
```
