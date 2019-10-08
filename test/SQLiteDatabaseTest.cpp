#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>
#include "Constants.hpp"
#include "../SQLiteWrapper/SQLiteDatabase.hpp"

class SQLiteDatabaseTest : public ::testing::Test {
protected:
	void SetUp() override {
		database = std::make_unique<SQLite::Database>(Constants::DB_FILE);
		database->execute(Constants::CREATE_TABLE);
	}

	std::unique_ptr<SQLite::Database> database;
};

TEST_F(SQLiteDatabaseTest, testFailsWhenUnknownFileWithNoOptionGiven) {
	EXPECT_THROW({ SQLite::Database o(Constants::UNKNOWN_FILE, 0); }, std::runtime_error);
}

TEST_F(SQLiteDatabaseTest, testOKWhenUnknownFileWithDefaultOptionGiven) {
	EXPECT_NO_THROW({ SQLite::Database o(Constants::UNKNOWN_FILE); });
}

TEST_F(SQLiteDatabaseTest, testExecuteSimpleQueries) {
	EXPECT_EQ(1, database->execute(Constants::INSERT_DATA));
	EXPECT_THROW(database->execute(Constants::INSERT_DATA), std::runtime_error);
}

TEST_F(SQLiteDatabaseTest, testCreateInvalidStatements) {
	EXPECT_THROW(database->prepare("INVALID STATEMENT"), std::runtime_error);
}
