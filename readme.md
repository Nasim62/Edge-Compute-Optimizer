
# EdgeComputeOptimizer

This repository contains the implementation of various content placement strategies in edge networks, including centralized, decentralized, coordinated, and a proposed approach. The project is based on real-world data and evaluates the effectiveness of these strategies for optimizing content distribution and improving hit ratios.

## Project Overview
Edge networks bring computational resources closer to end-users, reducing latency and improving response times. This project explores and implements multiple approaches for content placement in edge networks to determine the most efficient strategy.

### Key Approaches Implemented
1. **Centralized Approach**: Task scheduling and service provisioning are managed by a centralized controller. This method is a benchmark due to its global optimization capabilities but suffers from higher communication overhead.
2. **Decentralized Approach**: Each node independently manages content placement, offering flexibility but with a trade-off in coordination.
3. **Coordinated Approach**: Combines centralized provisioning with decentralized task scheduling for a balance of efficiency and flexibility.
4. **Proposed Approach**: A novel strategy aiming to improve hit ratios and reduce overhead by leveraging peer-to-peer communication and optimized resource allocation.

## Features
- Processes real-world datasets to analyze the performance of each approach.
- Uses Python for preprocessing data and C++ for implementing strategies.
- Provides a detailed comparison of hit ratios and resource utilization across different strategies.

## Files in the Repository
1. **`8522.cpp`**: Provided by the instructor, implements centralized, decentralized, coordinated, and proposed approaches.
2. **`duiet_proposed.cpp`**: Contains modifications and enhancements based on the proposed strategy.
3. **`filter_data.py`**: Filters the dataset to retain relevant fields and maps categorical values to integers.
4. **`format_data.py`**: Further processes the filtered data for use in the C++ implementations.

## Dataset
The project uses the Spotify track chart dataset (2014-2022) from Kaggle:
- **Link**: [Spotify Chart Data](https://www.kaggle.com/datasets/jfreyberg/spotify-chart-data)
- **Fields Used**:
  - `date` → **Arrival Time**
  - `duration % 1000` → **Deadline**
  - `country` → **Leaf Computation Spot**
  - `artist_genres` → **Service Type**

### Data Preprocessing
- **`filter_data.py`**:
  - Extracts necessary columns: `date`, `country`, `artist_genres`, `duration`.
  - Maps country names to integer codes.
  - Filters records based on the specified countries.
- **`format_data.py`**:
  - Converts categorical fields (e.g., `date`, `artist_genres`) to integers.
  - Outputs a formatted file ready for use by the C++ implementations.

## How to Use
1. **Preprocess the Dataset**:
   - Run `filter_data.py` to filter and map required data.
   - Use `format_data.py` to format the output for the C++ code.
2. **Run the C++ Implementations**:
   - Use `8522.cpp` to compare centralized, decentralized, and coordinated approaches.
   - Run `duiet_proposed.cpp` to test the proposed strategy.
3. **Analyze Results**:
   - Compare hit ratios, service provisioning efficiency, and overhead across approaches.

## Example Commands
### Python Scripts
```bash
python filter_data.py
python format_data.py
```

### Compile and Run C++ Code
```bash
g++ -o centralized 8522.cpp
./centralized
g++ -o proposed duiet_proposed.cpp
./proposed
```

## Results and Insights
The project demonstrates:
- The strengths and weaknesses of centralized, decentralized, and coordinated approaches.
- My proposed approach achieves a hit ratio of 99% with reduced provisioning overhead.

