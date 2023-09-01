#include <iostream>
#include "sql_query_builder.h"

int main()
{
    sql_query_builder query_builder;
    query_builder.AddColumn("name").AddColumn("phone");
    query_builder.AddFrom("students");
    query_builder.AddWhere("id", "42").AddWhere("name", "John");

    std::cout << query_builder.BuildQuery() << std::endl;
    std::cout << "SELECT name, phone FROM students WHERE id=42 AND name=John;" << std::endl;

    query_builder.AddFrom("students");
    std::cout << query_builder.BuildQuery() << std::endl;

    query_builder.AddWhere("name", "John").AddColumn("name");
    query_builder.AddColumn("phone").AddFrom("students");
    query_builder.AddWhere("id", "42");

    std::cout << query_builder.BuildQuery() << std::endl;
    std::cout << "SELECT name, phone FROM students WHERE id=42 AND name=John;" << std::endl;

    query_builder.AddWhere({ { "name", "John" }, { "id", "42" } }).AddColumns({ "name", "phone" }).AddFrom("students");

    std::cout << query_builder.BuildQuery() << std::endl;
    std::cout << "SELECT name, phone FROM students WHERE id=42 AND name=John;" << std::endl;
}
