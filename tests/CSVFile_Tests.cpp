#include <gtest/gtest.h>

#include <CSVFile.hpp>

using namespace std::string_literals;

TEST(CSVFile_Test, csv1_Test) {
#ifdef _WIN32
    csv::CSVFile file("..\\..\\data\\csv1.csv"s);
#else
    csv::CSVFile file("../../data/csv1.csv");
#endif
}

TEST(CSVFile_Test, csv2_Test) {
#ifdef _WIN32
    csv::CSVFile file("..\\..\\data\\csv2.csv"s);
#else
    csv::CSVFile file("../../data/csv2.csv");
#endif
}

TEST(CSVFile_Test, csv3_Test) {
#ifdef _WIN32
    csv::CSVFile file("..\\..\\data\\csv3.csv"s);
#else
    csv::CSVFile file("../../data/csv3.csv");
#endif
}

TEST(CSVFile_Test, csv4_Test) {
#ifdef _WIN32
    csv::CSVFile file("..\\..\\data\\csv4.csv"s);
#else
    csv::CSVFile file("../../data/csv4.csv");
#endif
}

TEST(CSVFile_Test, csv5_Test) {
#ifdef _WIN32
    csv::CSVFile file("..\\..\\data\\csv5.csv"s);
#else
    csv::CSVFile file("../../data/csv5.csv");
#endif
}

