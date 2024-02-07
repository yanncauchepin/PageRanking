# PageRank Algorithm in C #

This code implements the PageRank algorithm to calculate the importance of web pages. It is designed to work with input data provided in ***TSV*** format, where each line represents a path taken by users in the Wikispeedia game.

## Prerequisites ##

Before running this code, ensure you have the following :

- ***gcc*** compiler installed on your system.
- Input data in *TSV* format containing user paths. Some examples are located in the **Dataset** directory.
    - The names of articles must be URL-encoded.
    - Articles in a path are separated by ";".
    - Back clicks are represented by "<".

## Usage ##

1. Navigate to the **Code** directory containing the source code and the ***Makefile*** file.
2. Compile the code by running ***make all***.
```bash
make all
```
3. Execute the compiled program by running ***./pageranking ../Dataset/input_file.tsv***, where ***../Dataset/input_file.tsv*** is the path to the ***TSV*** file containing the input data.
```bash
./pageranking ../Dataset/input_file.tsv
```

### Example ###

```bash
cd Code
make all
./pageranking ../Dataset/paths_finished.tsv
```

### Monitor ###

To configure the parameters for the PageRank algorithm, the user have to inform values during the running of the program. In chronological order, the user have to provide :
- **Damping Factor** : Float value between 0 and 1.
- **Convergence Threshold** : Integer value which indicates the negative logarithmic power.
- **Classical or Customized Ranking** : Integer value between 0 and 1 which indicates if the program initialize a classical or a customized ranking.
- *(Optional)* **Customized Websites** : If selecting customized ranking, string character iteration which indicates the names of websites to customized. ***'None'*** to stop the scan iteration.

## Results ##

The program will display the 20 websites with the highest scores in the terminal. Additionally, the scores for all websites will be saved in the **Output** directory in the file named ***output.txt***.

## To do list (self) ##
