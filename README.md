Movie Recommendation System
This project implements a simple movie recommendation system using collaborative filtering based on user ratings. The system reads user ratings from a training file and recommends movies to users based on their similarity to other users.

Features
Reading User Ratings: Reads user ratings from a training file. Each rating entry contains a user ID, an item (movie) ID, and a rating.
Calculating User Average Ratings: Calculates the average rating for each user to normalize the ratings.
Cosine Similarity Calculation: Calculates the similarity between users using the cosine similarity formula based on their ratings.
Movie Recommendation: Recommends movies to a user based on the ratings of other similar users using a collaborative filtering approach.
Error Handling: Includes robust error handling for reading and processing input files.
Code Overview
evaluate_movies: Compares movie ratings.
str_to_int: Converts a string to an integer with error handling.
read_users_rating: Reads user ratings from a CSV file and stores them in a data structure.
rating_average: Computes the average rating for each user.
get_similarity: Calculates the cosine similarity between users based on their ratings.
movie_recommendation: Recommends movies to a user based on the similarity to other users and their ratings.
clear_all: Clears all stored data structures to reset the system.
main: Interacts with the user to read file names, process data, and display movie recommendations.
