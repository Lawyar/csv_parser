#include <gtest/gtest.h>

#include <CSVRow.hpp>

using csv::CSVRow;

using rowRecord = std::pair<size_t, std::vector<std::string>>;

using namespace std::string_literals;

TEST(Row_Test, Row_CTor) {
    const std::string recordCell1 = "mama"s;
    const std::string recordCell2 = "papa"s;
    const std::vector<std::string> cellSeq{recordCell1, recordCell2};
    constexpr size_t recordIndex = 1;
    const rowRecord rec{ recordIndex, cellSeq };

    EXPECT_NO_THROW(CSVRow{ rec });
}

TEST(Row_Test, Row_MoveCTor) {
    const std::string recordCell1 = "mama"s;
    const std::string recordCell2 = "papa"s;
    const std::vector<std::string> cellSeq{ recordCell1, recordCell2 };
    constexpr size_t recordIndex = 1;
    rowRecord rec{ recordIndex, cellSeq };

    EXPECT_NO_THROW(CSVRow{ std::move(rec) });
}

TEST(Row_Test, Row_CheckPairCast) {
    const std::string recordCell1 = "mama"s;
    const std::string recordCell2 = "papa"s;
    const std::string recordCell3 = "granny"s;
    const std::vector<std::string> cellSeq{ recordCell1, recordCell2, recordCell3 };
    constexpr size_t recordIndex = 1;
    const rowRecord rec{ recordIndex, cellSeq };

    const CSVRow r{ rec };
    const rowRecord rCasted = r;
    EXPECT_EQ(rec, rCasted);
}

TEST(Row_Test, Row_CheckConstIndexing) {
    const std::string recordCell1 = "mama"s;
    const std::string recordCell2 = "papa"s;
    const std::string recordCell3 = "granny"s;
    const std::vector<std::string> cellSeq{ recordCell1, recordCell2, recordCell3 };
    constexpr size_t recordIndex = 1;
    const rowRecord rec{ recordIndex, cellSeq };
    const CSVRow r(rec);

    EXPECT_EQ(r[0], recordCell1);
    EXPECT_EQ(r[1], recordCell2);
    EXPECT_EQ(r[2], recordCell3);
}

TEST(Row_Test, Row_CheckIndexingOnChange) {
    const std::string recordCell1 = "mama"s;
    const std::string recordCell2 = "papa"s;
    const std::string recordCell3 = "granny"s;
    const std::vector<std::string> cellSeq{ recordCell1, recordCell2, recordCell3 };
    constexpr size_t recordIndex = 1;
    const rowRecord rec{ recordIndex, cellSeq };
    CSVRow r(rec);
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
    const std::string recordCell1 = "mama"s;
    const std::string recordCell2 = "papa"s;
    const std::string recordCell3 = "granny"s;
    const std::vector<std::string> cellSeq{ recordCell1, recordCell2, recordCell3 };
    constexpr size_t recordIndex = 15;
    const rowRecord rec{ recordIndex, cellSeq };

    const CSVRow r(rec);
    EXPECT_EQ(r.RowIndex(), recordIndex);
}

TEST(Row_Test, Row_CheckRowCells) {
    const std::string recordCell1 = "mama"s;
    const std::string recordCell2 = "papa"s;
    const std::string recordCell3 = "granny"s;
    const std::vector<std::string> cellSeq{ recordCell1, recordCell2, recordCell3 };
    constexpr size_t recordIndex = 15;
    const rowRecord rec{ recordIndex, cellSeq };

    const CSVRow r(rec);
    EXPECT_EQ(r.RowCells(), cellSeq);
}

TEST(Row_Test, Row_SetRecordCells) {
    const std::string recordCell1 = "mama"s;
    const std::string recordCell2 = "papa"s;
    const std::string recordCell3 = "granny"s;
    std::vector<std::string> cellSeq{ recordCell1, recordCell2, recordCell3 };
    constexpr size_t recordIndex = 15;
    const rowRecord rec{ recordIndex, cellSeq };

    CSVRow r(rec);
    std::reverse(cellSeq.begin(), cellSeq.end());
    r.SetRowCells(cellSeq);
    EXPECT_EQ(r.RowCells(), cellSeq);
}

TEST(Row_Test, Row_SetMoveRecordCells) {
    const std::string recordCell1 = "mama"s;
    const std::string recordCell2 = "papa"s;
    const std::string recordCell3 = "granny"s;
    std::vector<std::string> cellSeq{ recordCell1, recordCell2, recordCell3 };
    constexpr size_t recordIndex = 15;
    const rowRecord rec{ recordIndex, cellSeq };

    CSVRow r(rec);
    std::reverse(cellSeq.begin(), cellSeq.end());
    const std::vector<std::string> cellsNumberTmp = cellSeq;
    r.SetRowCells(std::move(cellSeq));
    EXPECT_EQ(r.RowCells(), cellsNumberTmp);
}
