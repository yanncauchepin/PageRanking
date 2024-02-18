# PageRank Algorithm #
> ### Language : C ###

This code implements the PageRank algorithm to calculate the importance of web pages. It is designed to work with input data provided in ***tsv*** format, where each line represents a path taken by users in the Wikispeedia game.

## Prerequisites ##

Before running this code, ensure you have the following :

- ***gcc*** compiler installed on your system.

## Input Dataset ##

The input dataset is in the ***tsv*** format and contain user paths. Some examples are located in the **Dataset** directory.
- The names of articles must be URL-encoded.
- Articles in a path are separated by
- Back clicks are represented by "<".

## Usage ##

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

### Example ###

```bash
cd code
make all
cd ..
./pagerank dataset/paths_finished.tsv
```

## Monitor ##

To configure the parameters for the PageRank algorithm, the user have to inform values during the execution of the program. In chronological order, the user have to provide :
- **Damping Factor** : Float value between 0 and 1.
- **Convergence Threshold** : Integer value which indicates the negative logarithmic power.
- **Classical or Customized Ranking** : Boolean 0 or 1 to indicate if the program initialize a classical or a customized ranking.
- *(Optional)* **Customized Websites** : If selecting customized ranking, string character iteration which indicates the names of websites to customized. ***'None'*** to stop the scan iteration.

## Results ##

The program will display the 20 websites with the highest scores in the terminal. Additionally, the scores for all websites will be saved in the **output** directory in the file named ***output.txt***.

## To do list ##

- [ ] Update the report in the Deprecated directory by using Latex.
- [ ] Check consistency of the input websites such as unfinished paths (Dataset/paths_unfinished.tsv) or others special features.
- [ ] Identify errors why results are identical and constant for any websites.
- [ ] Correct errors where some websites have same index in hashing function. Handle the case of same index or find solutions to return different indexes.
- [ ] Correct errors to adapt the hashing table according to the number of websites.
- [ ] Check how to free allocated memory of transition_matrix without having double free or corruption abordet core dumped
- [ ] Check whether there are website which are include into destination but not present in hashing_table due to lack of link to others websites.
- [ ] Check whether we have to change columns and row in the building of transition_matrix
- [ ] Check for a better hashing function and how to handle error in hashing, maybe size of hashing
- [ ] data test.tsv works but there is errors with paths_finished.tsv -> produced by free hashing table
- [ ] Adapt the repository to well developer traditions.
