<p align="center">
  <img src="featured_image.gif" alt="" width="80%">
</p>

---


# PageRank Algorithm 

This code implements the PageRank algorithm to compute the rank of web pages. It is designed to work with input data provided in ***tsv*** format, where each line represents a path taken by users in the Wikispedia game.

## Prerequisites 

Before running this code, you need to have

- ***gcc*** compiler installed on your system.

## Input Dataset 

The input dataset is in the ***tsv*** format and contain user paths. Some examples are located in the **dataset** directory.
- The names of articles must be URL-encoded.
- Articles in a path are separated by ';'.
- Back clicks are represented by "<".

## Usage

1. Navigate to the **code** directory containing the source code and the ***Makefile*** file.
```bash
cd code
```
2. Compile the code by running ***make all***.
```bash
make all
```
3. The compiled program ***pagerank*** is now located in the parent repository.
```bash
cd ..
```
4. Execute the compiled program by running ***./pagerank dataset/input_file.tsv***, where ***dataset/input_file.tsv*** is the path to the ***tsv*** file containing the input data.
```bash
./pagerank dataset/input_file.tsv
```
*(Optional)* 5. Clean the repository by running ***make clean*** in the **code** directory.
```bash
cd code
make clean
```

### Example

```bash
cd code
make all
cd ..
./pagerank dataset/paths_finished.tsv
```

## Monitor

To configure the parameters for the PageRank algorithm, the user have to inform values during the execution of the program. In chronological order, the user have to provide :
- **Damping Factor** : float value between 0 and 1.
- **Convergence Threshold** : integer value which indicates the negative logarithmic power.
- **Classical or Customized Ranking** : boolean 0 or 1 to indicate if the program initialize a classical or a customized ranking.
- *(Optional)* **Customized Websites** : if selecting customized ranking, an iterator over string character which indicates the names of websites to customized. ***'None'*** to stop the scan iteration.

## Results

The program will display the 20 websites with the highest scores in the terminal. Additionally, the scores for all websites will be saved in the **output** directory in the file named ***output.txt***.
