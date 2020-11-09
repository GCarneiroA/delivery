
#ifndef VERSION_HPP
#define VERSION_HPP

#include <Version.grpc.pb.h>

namespace delivery
{
    namespace version
    {

        class VersionCall
        {
        public:
            VersionCall(DeliveryVersion::AsyncService *service, grpc::ServerCompletionQueue *queue);
            void process();
        private:
            DeliveryVersion::AsyncService *m_service;
            grpc::ServerCompletionQueue *m_queue;
            grpc::ServerContext m_context;
            VersionRequest m_request;
            VersionResponse m_response;
            grpc::ServerAsyncResponseWriter<VersionResponse> m_responder;

            enum CallStatus { CREATE, PROCESS, FINISH };
            CallStatus m_status;
        };

        void handleVersion(DeliveryVersion::AsyncService *service, std::unique_ptr<grpc::ServerCompletionQueue> *queue);
    
    }
}

#endif
