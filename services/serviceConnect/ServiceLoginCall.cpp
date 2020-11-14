
#include "ServiceLoginCall.hpp"

namespace delivery
{
    namespace login
    {
        LoginCall::LoginCall(DeliveryLogin::AsyncService *service, grpc::ServerCompletionQueue *queue)
            : m_service(service)
            , m_queue(queue)
            , m_responder(&m_context)
            , m_status(CREATE)
        {
            process();
        }
        
        void LoginCall::process() 
        {
            if (m_status == CREATE) {
                m_status = PROCESS;
                m_service->RequestLogin(&m_context, &m_request, &m_responder, m_queue, m_queue, this);
            } else if (m_status == PROCESS) {
                new LoginCall(m_service, m_queue);

                std::string username = m_request.username();
                std::string password = m_request.password();
                if (username == "gustavo" || password == "der555") {
                    m_response.set_token("mytoken");
                    m_response.set_status(LoginResponse_Status_LOGGED);
                } else {
                    m_response.set_token("");
                    m_response.set_status(LoginResponse_Status_INVALID);
                }

                m_status = FINISH;
                m_responder.Finish(m_response, grpc::Status::OK, this);
            } else {
                GPR_ASSERT(m_status == FINISH);
                delete this;
            }
        }
        
        void handleLogin(DeliveryLogin::AsyncService *service, std::unique_ptr<grpc::ServerCompletionQueue> *queue) 
        {
            new LoginCall(service, queue->get());
            void *tag;
            bool ok;
            while (true) {
                GPR_ASSERT((*queue)->Next(&tag, &ok));
                GPR_ASSERT(&ok);
                static_cast<LoginCall*>(tag)->process();
            }
        }
        
    }
}