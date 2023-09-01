#include "sql_query_builder.h"

sql_query_builder::sql_query_builder() {}

sql_query_builder& sql_query_builder::AddColumn(const std::string& s) {
	_collum.push_back(s);
	return *this;
};

sql_query_builder& sql_query_builder::AddFrom(const std::string& s) {
	_from = s;
	return *this;
};

sql_query_builder& sql_query_builder::AddWhere(const std::string& collum, const std::string& value) {
	_where[collum] = value;
	return *this;
};

std::string sql_query_builder::BuildQuery() {
	std::string result = "SELECT ";
	if (_collum.empty()) {
		result += "* ";
	}
	else {
		for (const auto& s : _collum) {
			result += s;
			if (&s == &_collum.back()) {
				result += " ";
			}
			else {
				result += ", ";
			}
		}
	}
	result += "FROM " + _from;
	if (!_where.empty()) {
		result += " WHERE ";
		for (const auto& m : _where) {
			result += m.first + "=" + m.second;
			if (&m.first != &_where.rbegin()->first) {
				result += " AND ";
			}
		}
	}
	result += ";";
	_collum.clear();
	_from = "";
	_where.clear();
	return result;
};

sql_query_builder& sql_query_builder::AddWhere(const std::map<std::string, std::string>& kv) noexcept {
	for (const auto& m : kv) {
		_where[m.first] = m.second;
	}
	return *this;
}

sql_query_builder& sql_query_builder::AddColumns(const std::vector<std::string>& columns) noexcept {
	_collum.insert(_collum.end(), columns.begin(), columns.end());
	return *this;
}