# Movie Recommendation System

A C++ based movie recommendation system that recommends movies to users based on collaborative filtering.

## Features

- **Collaborative Filtering**: Calculates similarity between users to recommend movies.
- **Adjustable Recommendations**: Number of recommendations per user can be modified.
- **Efficient Data Storage**: Uses unordered maps for fast lookups and memory efficiency.

## File Structure

- **`movie_rec.h`**: Header file containing data structures and function declarations.
- **Training File**: CSV file with user ratings for various movies (`UserID,ItemID,Rating`).
- **Test File**: CSV file with movie details (`ID,UserID,ItemID`).

## Installation

1. **Clone the repository**:
   ```bash
   git clone https://github.com/yourusername/movierec.git
   ```
2. **Compile the program** using a C++ compiler:
   ```bash
   g++ main.cpp -o movierec
   ```
3. **Run the program**:
   ```bash
   ./movierec
   ```

## Usage

1. **Run the program** and enter file paths when prompted:
   ```
   Please type the test file:
   ```
2. **Confirm file names** as prompted.
3. The program will calculate and display movie recommendations for each user.

## Code Functions

- **`read_users_rating`**: Reads the training file and stores user ratings.
- **`rating_average`**: Calculates each user's average rating.
- **`get_similarity`**: Computes similarity scores between users.
- **`movie_recommendation`**: Recommends movies based on similarity scores.
- **`clear_all`**: Clears data to free memory.

## Example Output

```
10 recommended movies for user: 12345
Movie 1
Movie 2
...
```
