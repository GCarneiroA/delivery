
#ifndef USER_HPP
#define USER_HPP

#include <userTable.h>
#include <sqlpp11/sqlpp11.h>
#include <sqlpp11/mysql/mysql.h>

namespace mysql = sqlpp::mysql;

namespace delivery
{
    namespace user
    {

        class User
        {
        public:
            User(mysql::connection *connection);
            bool login(const std::string &username, const std::string &password);

        private:
            mysql::connection *m_connection;
            basic::User m_userTable;

        };

    }
}

#endif
