# Complex Numbers
This folder contains a template to work with complex numbers. It contains member functions and non-member functions to create the complex numbers and do basic operations like addition, multiplication and division, calculating magnitudes and do comparisons.
The implementation contains operators for outputting the number and also read complex numbers. The folder also contain an unittest done with cxxtestgen.

To compile the files, locate to the folder with the files. The header file Complex is compiled together with the test file and is tested by running the unittest. The Cxxtestgen must be in HOME path and in the same subfolder as below to work as instructed. Otherwise it can by locating Cxxtest by yourself.
1. Generate the test with ```python $HOME/cxxtest-4.4/bin/cxxtestgen --error-printer -o mytest.cpp test_complex.h```
2. Compile the files with ``g++ -o mytest mytest.cpp -I $HOME/cxxtest-4.4``
3. Run the .exe file with ``./mytest``
