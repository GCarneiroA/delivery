
#include "userCall.hpp"

#include "user.hpp"

#include <sqlpp11/sqlpp11.h>
#include <sqlpp11/mysql/mysql.h>

namespace delivery
{
    namespace user
    {
        UserCall::UserCall(UserLogin::AsyncService *service, grpc::ServerCompletionQueue *queue)
            : m_service(service)
            , m_queue(queue)
            , m_responder(&m_context)
            , m_status(CREATE)
        {
            process();
        }
        
        void UserCall::process()
        {
            if (m_status == CREATE) {
                m_status = PROCESS;
                m_service->RequestLogin(&m_context, &m_request, &m_responder, m_queue, m_queue, this);
            } else if (m_status == PROCESS) {
                new UserCall(m_service, m_queue);

                namespace mysql = sqlpp::mysql;
                auto config = std::make_shared<mysql::connection_config>();
                config->user = "root";
                config->password = "der555";
                config->database = "delivery";
                config->debug = true;
                mysql::connection db(config);
                User user(&db);

                bool login = user.login(m_request.username(), m_request.password());
                if (login) {
                    // TODO: generate and register token in database
                    m_response.set_token("mytoken");
                } else {
                    m_response.set_token("");
                }

                m_status = FINISH;
                m_responder.Finish(m_response, grpc::Status::OK, this);
            } else {
                GPR_ASSERT(m_status == FINISH);
                delete this;
            }
        }
        
        void handleLogin(UserLogin::AsyncService *service, std::unique_ptr<grpc::ServerCompletionQueue> *queue)
        {
            new UserCall(service, queue->get());
            void *tag;
            bool ok;
            while (true) {
                GPR_ASSERT((*queue)->Next(&tag, &ok));
                GPR_ASSERT(&ok);
                static_cast<UserCall*>(tag)->process();
            }
        }

    }
}
