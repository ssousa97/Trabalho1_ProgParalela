# Defining constants
SRC_PATH="./src"
BIN_PATH="./bin"

# Removing previous run's files
rm ${BIN_PATH}/*

# C files list
c_files=$(ls -1 ${SRC_PATH})

# Compiling the programs
for file in ${c_files}; do

    filename=${file//.c/}
    mpicc "${SRC_PATH}/${file}" -o "${BIN_PATH}/${filename}" -lm

done