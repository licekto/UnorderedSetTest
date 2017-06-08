# Readme

Simple application for measuring the performance of **std::unordered_set** with reserverd space and without.

## Description

1. Application loads records (base64 strings) from input file to **std::vector**
2. Runs measurement
..* Without reserverd space for records
..*  With reserved space for records
3. Measurement is run in given number of iterations (command line argument), resulting time is computed as an average
4. Times are measured with the **std::chrono** utilities

## Obtaining sample input

Generate your own *sample_input.txt* file with given number of records with:
	
	`genbigfile.pl <number_of_records>`
	
Or download one with 100000 records from: [sample_input.txt](https://uploadfiles.io/32348)

# Running the application

	`UnorderedSetStrings <filename> <number_of_iterations>`

# Output

Application writes measured times to the standard output

# Evaluation

`std::unordered_set with reserved space is faster.`
`Duration of version without reserved space: 322885`
`Duration of version with    reserved space: 199107`