#include <gtest/gtest.h>

#include <CSVFile.hpp>

TEST(CSVFile_Test, CTorTest) {
#ifdef _WIN32
    csv::CSVFile file("D:\\Data\\learning\\cpp\\csv_parser\\data\\csv1.csv");
#else
    csv::CSVFile file("/mnt/d/Data/learning/cpp/csv_parser/data/csv1.csv");
#endif
}
