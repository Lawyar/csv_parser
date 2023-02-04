#include <gtest/gtest.h>

#include <CSVRow.hpp>

using csv::CSVRow;
using csv::RowException;

using rowRecord = std::pair<size_t, std::vector<std::string>>;

using namespace std::string_literals;

TEST(Row_Test, Row_CTor) {
    constexpr size_t cellsNumber = 2;
    const std::string recordCell1 = "mama"s;
    const std::string recordCell2 = "papa"s;
    const std::vector<std::string> cellSeq{recordCell1, recordCell2};
    constexpr size_t recordIndex = 1;
    const rowRecord rec{ recordIndex, cellSeq };

    EXPECT_NO_THROW(CSVRow(rec, cellsNumber));
}

TEST(Row_Test, Row_MoveCTor) {
    constexpr size_t cellsNumber = 2;
    const std::string recordCell1 = "mama"s;
    const std::string recordCell2 = "papa"s;
    const std::vector<std::string> cellSeq{ recordCell1, recordCell2 };
    constexpr size_t recordIndex = 1;
    rowRecord rec{ recordIndex, cellSeq };

    EXPECT_NO_THROW(CSVRow(std::move(rec), cellsNumber));
}

TEST(Row_Test, Row_CTorIncons) {
    constexpr size_t cellsNumber = 5;
    const std::string recordCell1 = "mama"s;
    const std::string recordCell2 = "papa"s;
    const std::vector<std::string> cellSeq{ recordCell1, recordCell2 };
    constexpr size_t recordIndex = 1;
    const rowRecord rec{ recordIndex, cellSeq };

    EXPECT_THROW(CSVRow(rec, cellsNumber), RowException);
}

TEST(Row_Test, Row_MoveCTorIncons) {
    constexpr size_t cellsNumber = 5;
    const std::string recordCell1 = "mama"s;
    const std::string recordCell2 = "papa"s;
    const std::vector<std::string> cellSeq{ recordCell1, recordCell2 };
    constexpr size_t recordIndex = 1;
    rowRecord rec{ recordIndex, cellSeq };

    EXPECT_THROW(CSVRow(std::move(rec), cellsNumber), RowException);
}

TEST(Row_Test, Row_CheckPairCast) {
    constexpr size_t cellsNumber = 3;
    const std::string recordCell1 = "mama"s;
    const std::string recordCell2 = "papa"s;
    const std::string recordCell3 = "granny"s;
    const std::vector<std::string> cellSeq{ recordCell1, recordCell2, recordCell3 };
    constexpr size_t recordIndex = 1;
    const rowRecord rec{ recordIndex, cellSeq };

    const CSVRow r(rec, cellsNumber);
    const rowRecord rCasted = r;
    EXPECT_EQ(rec, rCasted);
}

TEST(Row_Test, Row_CheckConstIndexing) {
    constexpr size_t cellsNumber = 3;
    const std::string recordCell1 = "mama"s;
    const std::string recordCell2 = "papa"s;
    const std::string recordCell3 = "granny"s;
    const std::vector<std::string> cellSeq{ recordCell1, recordCell2, recordCell3 };
    constexpr size_t recordIndex = 1;
    const rowRecord rec{ recordIndex, cellSeq };
    const CSVRow r(rec, cellsNumber);

    EXPECT_EQ(r[0], recordCell1);
    EXPECT_EQ(r[1], recordCell2);
    EXPECT_EQ(r[2], recordCell3);
}

TEST(Row_Test, Row_CheckIndexingOnChange) {
    constexpr size_t cellsNumber = 3;
    const std::string recordCell1 = "mama"s;
    const std::string recordCell2 = "papa"s;
    const std::string recordCell3 = "granny"s;
    const std::vector<std::string> cellSeq{ recordCell1, recordCell2, recordCell3 };
    constexpr size_t recordIndex = 1;
    const rowRecord rec{ recordIndex, cellSeq };
    CSVRow r(rec, cellsNumber);
    auto newRC1 = recordCell1 + recordCell2;
    auto newRC2 = recordCell2 + recordCell3;
    auto newRC3 = recordCell3 + recordCell1;
    r[0] = newRC1;
    r[1] = newRC2;
    r[2] = newRC3;

    EXPECT_EQ(r[0], newRC1);
    EXPECT_EQ(r[1], newRC2);
    EXPECT_EQ(r[2], newRC3);
}

TEST(Row_Test, Row_CheckRecordIndex) {
    constexpr size_t cellsNumber = 3;
    const std::string recordCell1 = "mama"s;
    const std::string recordCell2 = "papa"s;
    const std::string recordCell3 = "granny"s;
    const std::vector<std::string> cellSeq{ recordCell1, recordCell2, recordCell3 };
    constexpr size_t recordIndex = 15;
    const rowRecord rec{ recordIndex, cellSeq };

    const CSVRow r(rec, cellsNumber);
    EXPECT_EQ(r.RecordIndex(), recordIndex);
}

TEST(Row_Test, Row_CheckRowCells) {
    constexpr size_t cellsNumber = 3;
    const std::string recordCell1 = "mama"s;
    const std::string recordCell2 = "papa"s;
    const std::string recordCell3 = "granny"s;
    const std::vector<std::string> cellSeq{ recordCell1, recordCell2, recordCell3 };
    constexpr size_t recordIndex = 15;
    const rowRecord rec{ recordIndex, cellSeq };

    const CSVRow r(rec, cellsNumber);
    EXPECT_EQ(r.RecordCells(), cellSeq);
}

TEST(Row_Test, Row_SetRecordCells) {
    constexpr size_t cellsNumber = 3;
    const std::string recordCell1 = "mama"s;
    const std::string recordCell2 = "papa"s;
    const std::string recordCell3 = "granny"s;
    std::vector<std::string> cellSeq{ recordCell1, recordCell2, recordCell3 };
    constexpr size_t recordIndex = 15;
    const rowRecord rec{ recordIndex, cellSeq };

    CSVRow r(rec, cellsNumber);
    std::reverse(cellSeq.begin(), cellSeq.end());
    r.SetRecordCells(cellSeq, cellsNumber);
    EXPECT_EQ(r.RecordCells(), cellSeq);
}

TEST(Row_Test, Row_SetMoveRecordCells) {
    constexpr size_t cellsNumber = 3;
    const std::string recordCell1 = "mama"s;
    const std::string recordCell2 = "papa"s;
    const std::string recordCell3 = "granny"s;
    std::vector<std::string> cellSeq{ recordCell1, recordCell2, recordCell3 };
    constexpr size_t recordIndex = 15;
    const rowRecord rec{ recordIndex, cellSeq };

    CSVRow r(rec, cellsNumber);
    std::reverse(cellSeq.begin(), cellSeq.end());
    const std::vector<std::string> cellsNumberTmp = cellSeq;
    r.SetRecordCells(std::move(cellSeq), cellsNumber);
    EXPECT_EQ(r.RecordCells(), cellsNumberTmp);
}
