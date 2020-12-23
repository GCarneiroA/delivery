
#include "user.hpp"

#include <iostream>

namespace delivery
{
    namespace user
    {

        SQLPP_ALIAS_PROVIDER(total)

        User::User(mysql::connection *connection)
            : m_connection(connection)
        {
        }
        
        bool User::login(const std::string &username, const std::string &password) 
        {
            const auto &row = m_connection->run
            (
                select(all_of(m_userTable), select(sum(m_userTable.id))).from(m_userTable)
                    .where(m_userTable.username == username and m_userTable.password == password)
            );
            return (row.front().sum == 1);
        }
    }
}
