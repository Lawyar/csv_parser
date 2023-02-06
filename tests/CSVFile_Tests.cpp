#include <gtest/gtest.h>

#include <CSVFile.hpp>

TEST(CSVFile_Test, csv1_Test) {
#ifdef _WIN32
    csv::CSVFile file("D:\\Data\\learning\\cpp\\csv_parser\\data\\csv1.csv");
#else
    csv::CSVFile file("/mnt/d/Data/learning/cpp/csv_parser/data/csv1.csv");
#endif
}

TEST(CSVFile_Test, csv2_Test) {
#ifdef _WIN32
    csv::CSVFile file("D:\\Data\\learning\\cpp\\csv_parser\\data\\csv2.csv");
#else
    csv::CSVFile file("/mnt/d/Data/learning/cpp/csv_parser/data/csv2.csv");
#endif
}

TEST(CSVFile_Test, csv3_Test) {
#ifdef _WIN32
    csv::CSVFile file("D:\\Data\\learning\\cpp\\csv_parser\\data\\csv3.csv");
#else
    csv::CSVFile file("/mnt/d/Data/learning/cpp/csv_parser/data/csv3.csv");
#endif
}

TEST(CSVFile_Test, csv4_Test) {
#ifdef _WIN32
    csv::CSVFile file("D:\\Data\\learning\\cpp\\csv_parser\\data\\csv4.csv");
#else
    csv::CSVFile file("/mnt/d/Data/learning/cpp/csv_parser/data/csv4.csv");
#endif
}

TEST(CSVFile_Test, csv5_Test) {
#ifdef _WIN32
    csv::CSVFile file("D:\\Data\\learning\\cpp\\csv_parser\\data\\csv5.csv");
#else
    csv::CSVFile file("/mnt/d/Data/learning/cpp/csv_parser/data/csv5.csv");
#endif
}

