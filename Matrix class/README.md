# Matrix template class
This is a template implementation for a matrix class that is able to create matrices with a default-, move-, and copy-constructor. The template also contains accessors, chainable and non-chainable methods for matrix-operations.
Matrices in this implementation can also be printed in readable format and be edited by inserting, appending and removing rows and columns. This folder also contains a unittest for testing this implementation.

To compile the files, locate to the folder with the files. The header file Matrix is compiled together with the test file and is tested by running the unittest. The Cxxtestgen must be in HOME path and in the same subfolder as below to work as instructed. Otherwise it can by locating Cxxtest by yourself.
1. Generate the test with ```python $HOME/cxxtest-4.4/bin/cxxtestgen --error-printer -o myrunner.cpp mytest.h``` python3 can be used instead of python depending on what python is installed on the computer.
2. Compile the files with ``g++ -o mytest_runner myrunner.cpp -I $HOME/cxxtest-4.4``
3. Run the .exe file with ``./mytest_runner``

