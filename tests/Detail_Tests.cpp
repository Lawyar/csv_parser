#include <gtest/gtest.h>

#include <detail.hpp>

#include <filesystem>

using namespace detail_;
using namespace std::string_literals;
namespace fs = std::filesystem;

namespace {
    bool splitComp(const std::string& strSrc,
                   const std::vector<std::string>& expected, 
                   char delim) {
        const std::vector<std::string> real = strSplit(strSrc, expected.size(), delim);
        
        for (size_t i = 0; i < expected.size(); i++) {
            if (expected[i] != real[i]) {
                return false;
            }
        }

        return true;
    }
}

// detail_::genDefaultOutName
TEST(Detail_Test, genDefaultOutName_Default) {
    fs::path tPath("whereyouareboy");
    tPath /= "src.txt";
    fs::path expected("whereyouareboy");
    expected /= "src_out.txt";
    EXPECT_EQ(expected, genDefaultOutName(tPath));
}

TEST(Detail_Test, genDefaultOutName_DefaultOnEmpty) {
    fs::path tPath("");
    fs::path expected("_out.txt");
    EXPECT_EQ(expected, genDefaultOutName(tPath));
}

TEST(Detail_Test, genDefaultOutName_OnEmpty) {
    fs::path tPath("");
    std::string postfix = "brat"s, extension = "sestra"s;
    std::string expectedStr = postfix + '.' + extension;
    fs::path expected(expectedStr);
    EXPECT_EQ(expected, genDefaultOutName(tPath, postfix, extension));
}

#ifdef _WIN32
TEST(Detail_Test, genDefaultOutName_OnWinPath) {
    fs::path tPath("D:\\Puffy\\");
    std::string postfix = "brat"s, extension = "sestra"s;
    std::string expectedStr = tPath.string() + postfix + '.' + extension;
    fs::path expected(expectedStr);
    EXPECT_EQ(expected, genDefaultOutName(tPath, postfix, extension));
}
#else
TEST(Detail_Test, genDefaultOutName_OnUNIXPath) {
    fs::path tPath("/d/Puffy/");
    std::string postfix = "brat"s, extension = "sestra"s;
    std::string expectedStr = postfix + '.' + extension;
    fs::path expected(expectedStr);
    EXPECT_EQ(expected, genDefaultOutName(tPath, postfix, extension));
}
#endif  // #ifdef _WIN32

TEST(Detail_Test, genDefaultOutName_OnSpecPath) {
    fs::path tPath("chemical");
    tPath /= "subdir";
    tPath /= "file";
    std::string postfix = "sulfat"s, extension = "zinc"s;
    std::string expectedStr = tPath.string() + postfix + '.' + extension;
    fs::path expected(expectedStr);
    EXPECT_EQ(expected, genDefaultOutName(tPath, postfix, extension));
}

// detail_::strSplit

TEST(Detail_Test, strSplit_OnEmpty) {
    const std::string str = ""s;
    const std::vector<std::string> expected{ ""s };

    EXPECT_TRUE(splitComp(str, expected, '.'));
}

TEST(Detail_Test, strSplit_Test1) {
    const std::string str = "Masha,Vasha,,Vot,Ona";
    const std::vector<std::string> expected{ "Masha"s, "Vasha"s,""s,"Vot"s,"Ona"s };

    EXPECT_TRUE(splitComp(str, expected, ','));
}

TEST(Detail_Test, strSplit_Test2) {
    const std::string str = "Masha. Vasha . .     Vot.Ona ";
    const std::vector<std::string> expected{ "Masha"s, " Vasha "s," "s,"     Vot"s,"Ona "s };

    EXPECT_TRUE(splitComp(str, expected, '.'));
}

TEST(Detail_Test, strSplit_Test3) {
    const std::string str = "Masha,Vasha,,Vot,Ona";
    const std::vector<std::string> expected{ "Masha,Vasha,,Vot,Ona"s };

    EXPECT_TRUE(splitComp(str, expected, '.'));
}
