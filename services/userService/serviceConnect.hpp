
#ifndef SERVICECONNECT_HPP
#define SERVICECONNECT_HPP

#include <grpcpp/grpcpp.h>
#include <grpc/support/log.h>

#include "userCall.hpp"

namespace delivery
{
    using namespace user;

    namespace service
    {
        namespace user
        {

            class UserService final
            {
            public:
                ~UserService();
                void run();

            private:
                UserLogin::AsyncService m_userLoginService;
                std::vector<std::unique_ptr<grpc::ServerCompletionQueue>> m_cq;
                std::unique_ptr<grpc::Server> m_server;
            };

        }
    }
}

#endif
