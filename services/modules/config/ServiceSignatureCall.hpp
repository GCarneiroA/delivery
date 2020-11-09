
#ifndef SIGNATURE_HPP
#define SIGNATURE_HPP

#include <Signature.grpc.pb.h>

namespace delivery
{
    namespace signature
    {

        class SignatureCall
        {
        public:
            SignatureCall(DeliverySignature::AsyncService *service, grpc::ServerCompletionQueue *queue);
            void process();
        private:
            DeliverySignature::AsyncService *m_service;
            grpc::ServerCompletionQueue *m_queue;
            grpc::ServerContext m_context;
            SignatureRequest m_request;
            SignatureResponse m_response;
            grpc::ServerAsyncResponseWriter<SignatureResponse> m_responder;

            enum CallStatus { CREATE, PROCESS, FINISH };
            CallStatus m_status;
        };

        void handleSignature(DeliverySignature::AsyncService *service, std::unique_ptr<grpc::ServerCompletionQueue> *queue);

    }
}

#endif
