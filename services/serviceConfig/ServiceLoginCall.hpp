
#ifndef LOGIN_HPP
#define LOGIN_HPP

#include <Login.grpc.pb.h>

namespace delivery
{
    namespace login
    {

        class LoginCall
        {
        public:
            LoginCall(DeliveryLogin::AsyncService *service, grpc::ServerCompletionQueue *queue);
            void process();
        private:
            DeliveryLogin::AsyncService *m_service;
            grpc::ServerCompletionQueue *m_queue;
            grpc::ServerContext m_context;
            LoginRequest m_request;
            LoginResponse m_response;
            grpc::ServerAsyncResponseWriter<LoginResponse> m_responder;

            enum CallStatus { CREATE, PROCESS, FINISH };
            CallStatus m_status;
        };

        void handleLogin(DeliveryLogin::AsyncService *service, std::unique_ptr<grpc::ServerCompletionQueue> *queue);

    }
}

#endif
