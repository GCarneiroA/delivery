
#ifndef USERCALL_HPP
#define USERCALL_HPP

#include "user.grpc.pb.h"

namespace delivery
{
    namespace user
    {

        class UserCall
        {
        public:
            UserCall(UserLogin::AsyncService *service, grpc::ServerCompletionQueue *queue);
            void process();
        private:
            UserLogin::AsyncService *m_service;
            grpc::ServerCompletionQueue *m_queue;
            grpc::ServerContext m_context;
            LoginRequest m_request;
            LoginResponse m_response;
            grpc::ServerAsyncResponseWriter<LoginResponse> m_responder;

            enum CallStatus { CREATE, PROCESS, FINISH };
            CallStatus m_status;
        };

        void handleLogin(UserLogin::AsyncService *service, std::unique_ptr<grpc::ServerCompletionQueue> *queue);

    }
}

#endif  // USERCALL_HPP
