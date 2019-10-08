#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "Constants.hpp"
#include "../SQLiteWrapper/SQLiteDatabase.hpp"

class SQLiteStatementTest : public ::testing::Test {
protected:
	void SetUp() override {
		database = std::make_unique<SQLite::Database>(Constants::DB_FILE);
		database->execute(Constants::CREATE_TABLE);
	}

	std::unique_ptr<SQLite::Database> database;
};

TEST_F(SQLiteStatementTest, testExecutePreparedStatement) {
	auto stmt = database->prepare(Constants::INSERT_DATA);
	EXPECT_EQ(1, stmt.execute());
	EXPECT_THROW(stmt.execute(), std::runtime_error);
}

TEST_F(SQLiteStatementTest, testBindArguments) {
	auto stmt = database->prepare(Constants::INSERT_PREPARED_STMT);
	stmt.bind(1, 1).bind(2, 2.0).bind(":third", "three").bind(":fourth");
	EXPECT_EQ(1, stmt.execute());
}

TEST_F(SQLiteStatementTest, testResetAndBindArguments) {
	auto stmt = database->prepare("INSERT INTO Test VALUES (?, 0.0, NULL, NULL)");
	stmt.bind(1, 1).execute();
	stmt.reset();
	stmt.bind(1, 2).execute();
	EXPECT_EQ(2, database->execute("UPDATE Test SET second = 2.0"));
}

TEST_F(SQLiteStatementTest, testFetchRows) {
	database->execute("INSERT INTO Test VALUES (1, 0.0, NULL, NULL)");
	database->execute("INSERT INTO Test VALUES (2, 0.0, NULL, NULL)");
	auto stmt = database->prepare(Constants::SELECT_ALL_DATA);
	EXPECT_TRUE(stmt.fetch());
	EXPECT_TRUE(stmt.fetch());
	EXPECT_FALSE(stmt.fetch());
}

TEST_F(SQLiteStatementTest, testGetColumnFailsWhenInvalidIndexGiven) {
	database->execute(Constants::INSERT_DATA);
	auto stmt = database->prepare(Constants::SELECT_ALL_DATA);
	EXPECT_THROW(stmt.getColumn(100), std::runtime_error);
	EXPECT_THROW(stmt.getColumn("unknown"), std::runtime_error);
}
