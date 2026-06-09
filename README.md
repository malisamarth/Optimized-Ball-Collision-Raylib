# Optimized-Ball-Collision-Raylib
Grid-based cell checking collision algorithm.

# Overview
<img width="505.5" height="445.5" alt="overview drawio" src="https://github.com/user-attachments/assets/6b2abee1-57a5-4ee7-ba91-717c5e05fb2a" />

This project demonstrates collision detection optimization in a 2D Raylib simulation.

- Written in C++ using Raylib
- Simulates moving balls with real-time collision detection
- Tracks collision checks per frame
- Compares brute-force collision detection against a grid-based spatial partitioning approach
- Measures the performance improvement achieved through optimization

# Unoptimized Collision Check
<img width="600.5" height="601" alt="unoptimized drawio" src="https://github.com/user-attachments/assets/f18cc0f6-611d-4dd8-bd8b-2ac17f4990e3" />

The initial implementation uses a brute-force approach where every ball is compared against every other ball.

- Two nested loops iterate through all ball pairs.
- `CheckCollisionCircles()` is executed for each comparison.
- Collision checks grow quadratically as object count increases.
- Complexity: **O(n²)**

For 100 balls:

- **4,950 collision checks per frame**

## Optimized Collision Check (Uniform Grid)
<img width="766" height="901" alt="optimized drawio" src="https://github.com/user-attachments/assets/f8e0c360-f143-49a0-a2ff-d74682c91097" />

The simulation space is divided into fixed-size cells. Each ball is assigned to a cell based on its position.

- Collision checks are limited to balls in the same cell.
- Neighboring cells are also checked to avoid missing edge collisions.
- Distant objects are ignored.
- Significantly reduces unnecessary comparisons.

For 100 balls:

- **~1,594 collision checks per frame**
- **~67.8% reduction**

## Results

| Balls | Method | Checks |
|---------|---------|---------|
| 100 | Brute Force | 4950 |
| 100 | Uniform Grid | 1594 |

Reduction: **~67.8% fewer collision checks**

