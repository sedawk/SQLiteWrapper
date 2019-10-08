#pragma once

#include <sqlite3.h>
#include <memory>
#include <string>

namespace SQLite {

	class Statement {
	public:
		explicit Statement(sqlite3_stmt* statement);

		int execute();
		void reset();

		Statement& bind(const int index, const int value);
		Statement& bind(const int index, const unsigned int value);
		Statement& bind(const int index, const long long value);
		Statement& bind(const int index, const double value);
		Statement& bind(const int index, const std::string& value);
		Statement& bind(const int index, const char* value);
		Statement& bind(const int index, const void* value, int size);
		Statement& bind(const int index);

		Statement& bind(const std::string& name, const int value);
		Statement& bind(const std::string& name, const unsigned int value);
		Statement& bind(const std::string& name, const long long value);
		Statement& bind(const std::string& name, const double value);
		Statement& bind(const std::string& name, const std::string& value);
		Statement& bind(const std::string& name, const char* value);
		Statement& bind(const std::string& name, const void* value, int size);
		Statement& bind(const std::string& name);

	private:
		void checkReturn(int status);
		sqlite3* getDB();
		sqlite3_stmt* getStmt();

		std::unique_ptr<sqlite3_stmt, int(*)(sqlite3_stmt*)> mStatement;
	};
}