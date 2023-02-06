#include <gtest/gtest.h>

#include <CSVRow.hpp>

using csv::CSVRow;

using rowRecord = std::pair<size_t, std::vector<std::unique_ptr<csv::Cell>>>;

using namespace std::string_literals;

TEST(Row_Test, Row_CTor) {
    const std::string recordCell1 = "mama"s;
    const std::string recordCell2 = "papa"s;
    std::vector<std::unique_ptr<csv::Cell>> cellSeq;
    cellSeq.push_back(std::make_unique<csv::Cell>(recordCell1));
    cellSeq.push_back(std::make_unique<csv::Cell>(recordCell2));
    constexpr size_t recordIndex = 1;
    const rowRecord rec{ recordIndex, std::move(cellSeq) };

    EXPECT_NO_THROW(CSVRow{ rec });
}

TEST(Row_Test, Row_MoveCTor) {
    const std::string recordCell1 = "mama"s;
    const std::string recordCell2 = "papa"s;
    std::vector<std::unique_ptr<csv::Cell>> cellSeq;
    cellSeq.push_back(std::make_unique<csv::Cell>(recordCell1));
    cellSeq.push_back(std::make_unique<csv::Cell>(recordCell2));
    constexpr size_t recordIndex = 1;
    rowRecord rec{ recordIndex, std::move(cellSeq) };

    EXPECT_NO_THROW(CSVRow{ std::move(rec) });
}

TEST(Row_Test, Row_CheckPairCast) {
    const std::string recordCell1 = "mama"s;
    const std::string recordCell2 = "papa"s;
    const std::string recordCell3 = "granny"s;
    std::vector<std::unique_ptr<csv::Cell>> cellSeq;
    cellSeq.push_back(std::make_unique<csv::Cell>(recordCell1));
    cellSeq.push_back(std::make_unique<csv::Cell>(recordCell2));
    cellSeq.push_back(std::make_unique<csv::Cell>(recordCell3));
    constexpr size_t recordIndex = 1;
    const rowRecord rec{ recordIndex, std::move(cellSeq) };

    const CSVRow r{ rec };
    const rowRecord rCasted = r;
    EXPECT_EQ(*rec.second[0], *rCasted.second[0]);
    EXPECT_EQ(*rec.second[1], *rCasted.second[1]);
    EXPECT_EQ(*rec.second[2], *rCasted.second[2]);
}

TEST(Row_Test, Row_CheckConstIndexing) {
    const std::string recordCell1 = "mama"s;
    const std::string recordCell2 = "papa"s;
    const std::string recordCell3 = "granny"s;
    std::vector<std::unique_ptr<csv::Cell>> cellSeq;
    cellSeq.push_back(std::make_unique<csv::Cell>(recordCell1));
    cellSeq.push_back(std::make_unique<csv::Cell>(recordCell2));
    cellSeq.push_back(std::make_unique<csv::Cell>(recordCell3));
    constexpr size_t recordIndex = 1;
    const rowRecord rec{ recordIndex, std::move(cellSeq) };
    const CSVRow r(rec);

    EXPECT_EQ(r[0].ToString(), recordCell1);
    EXPECT_EQ(r[1].ToString(), recordCell2);
    EXPECT_EQ(r[2].ToString(), recordCell3);
}

TEST(Row_Test, Row_CheckIndexingOnChange) {
    const std::string recordCell1 = "mama"s;
    const std::string recordCell2 = "papa"s;
    const std::string recordCell3 = "granny"s;
    std::vector<std::unique_ptr<csv::Cell>> cellSeq;
    cellSeq.push_back(std::make_unique<csv::Cell>(recordCell1));
    cellSeq.push_back(std::make_unique<csv::Cell>(recordCell2));
    cellSeq.push_back(std::make_unique<csv::Cell>(recordCell3));
    constexpr size_t recordIndex = 1;
    const rowRecord rec{ recordIndex, std::move(cellSeq) };
    CSVRow r(rec);
    auto newRC1 = recordCell1 + recordCell2;
    auto newRC2 = recordCell2 + recordCell3;
    auto newRC3 = recordCell3 + recordCell1;
    r[0] = newRC1;
    r[1] = newRC2;
    r[2] = newRC3;

    EXPECT_EQ(r[0].ToString(), newRC1);
    EXPECT_EQ(r[1].ToString(), newRC2);
    EXPECT_EQ(r[2].ToString(), newRC3);
}

TEST(Row_Test, Row_CheckRecordIndex) {
    const std::string recordCell1 = "mama"s;
    const std::string recordCell2 = "papa"s;
    const std::string recordCell3 = "granny"s;
    std::vector<std::unique_ptr<csv::Cell>> cellSeq;
    cellSeq.push_back(std::make_unique<csv::Cell>(recordCell1));
    cellSeq.push_back(std::make_unique<csv::Cell>(recordCell2));
    cellSeq.push_back(std::make_unique<csv::Cell>(recordCell3));
    constexpr size_t recordIndex = 15;
    const rowRecord rec{ recordIndex, std::move(cellSeq) };

    const CSVRow r(rec);
    EXPECT_EQ(r.RowIndex(), recordIndex);
}

TEST(Row_Test, Row_CheckRowCells) {
    const std::string recordCell1 = "mama"s;
    const std::string recordCell2 = "papa"s;
    const std::string recordCell3 = "granny"s;
    std::vector<std::unique_ptr<csv::Cell>> cellSeq;
    cellSeq.push_back(std::make_unique<csv::Cell>(recordCell1));
    cellSeq.push_back(std::make_unique<csv::Cell>(recordCell2));
    cellSeq.push_back(std::make_unique<csv::Cell>(recordCell3));
    std::vector<std::unique_ptr<csv::Cell>> cellSeqCp;
    cellSeqCp.push_back(std::make_unique<csv::Cell>(recordCell1));
    cellSeqCp.push_back(std::make_unique<csv::Cell>(recordCell2));
    cellSeqCp.push_back(std::make_unique<csv::Cell>(recordCell3));
    constexpr size_t recordIndex = 15;
    const rowRecord rec{ recordIndex, std::move(cellSeq) };

    const CSVRow r(rec);
    EXPECT_EQ(*r.RowCells()[0], *cellSeqCp[0]);
    EXPECT_EQ(*r.RowCells()[1], *cellSeqCp[1]);
    EXPECT_EQ(*r.RowCells()[2], *cellSeqCp[2]);
}
