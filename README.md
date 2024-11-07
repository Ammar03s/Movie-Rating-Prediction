# Movie Recommendation System

This project implements a movie recommender system using collaborative filtering. The goal is to predict movie ratings for users based on their past ratings and the ratings of similar users.


## Features
- Calculates average user ratings
- Computes user similarity using cosine similarity
- Generates movie recommendations for each user based on their similarity to other users
- Supports clearing data structures and restarting the recommendation process


## Data Files
The program expects two data files:
1. **Training File**: Contains movie rating data in the format `user_id,item_id,rating`.
2. **Test File**: Contains user and movie information in the format `id,user_id,item_id`.

## Algorithms
The project implements 2 main collaborative filtering algorithms:

### User-Based Collaborative Filtering (UBCF)
To predict the rating of a user `u` for a movie `i`, the algorithm finds the `k` most similar users to `u` who have rated `i`, and then predicts the rating as the average of those `k` users' ratings for `i`.

The similarity between two users `u` and `v` is calculated using the cosine similarity formula:

```
cosine(u, v) = (u · v) / (||u|| * ||v||)
             = Σ(u_i * v_i) / (√(Σu_i^2) * √(Σv_i^2))
```

### Item-Based Collaborative Filtering (IBCF)
To predict the rating of a user `u` for a movie `i`, the algorithm finds the `k` most similar movies to `i` that have been rated by `u`, and then predicts the rating as the average of `u`'s ratings for those `k` movies.

The similarity between two movies `i` and `j` is also calculated using the cosine similarity formula, but in this case, the vectors represent the rating profiles of the movies across all users.

## Optimizations
To improve the efficiency of the recommender system, the project uses the following optimizations:
- Efficient data structures (e.g., unordered maps) to store and access the rating data.
- Careful selection of the number of similar users/items (`k`) to balance accuracy and performance.

## Example Output

```
10 recommended movies for user: 12345
Movie 1
Movie 2
...
```



## Evaluation
The performance of the recommender system is evaluated using the Root Mean Squared Error (RMSE) metric, which is defined as:

```
RMSE = sqrt(Σ(y_i - ŷ_i)^2 / n)
```

where `y_i` is the actual rating and `ŷ_i` is the predicted rating.


