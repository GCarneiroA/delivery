
#include "ServiceSignatureCall.hpp"

namespace delivery
{
    namespace signature
    {
        SignatureCall::SignatureCall(DeliverySignature::AsyncService *service, grpc::ServerCompletionQueue *queue)
            : m_service(service)
            , m_queue(queue)
            , m_responder(&m_context)
            , m_status(CREATE)
        {
            process();
        }
        
        void SignatureCall::process()
        {
            if (m_status == CREATE) {
                m_status = PROCESS;
                m_service->RequestSignature(&m_context, &m_request, &m_responder, m_queue, m_queue, this);
            } else if (m_status == PROCESS) {
                new SignatureCall(m_service, m_queue);

                const std::string sSignature("sig12xss92383");
                m_response.set_signaturevalid(sSignature == m_request.signature());
                
                m_status = FINISH;
                m_responder.Finish(m_response, grpc::Status::OK, this);
            } else {
                GPR_ASSERT(m_status == FINISH);
                delete this;
            }
        }
        
        void handleSignature(DeliverySignature::AsyncService *service, std::unique_ptr<grpc::ServerCompletionQueue> *queue) 
        {
            new SignatureCall(service, queue->get());
            void *tag;
            bool ok;
            while (true) {
                GPR_ASSERT((*queue)->Next(&tag, &ok));
                GPR_ASSERT(&ok);
                static_cast<SignatureCall*>(tag)->process();
            }
        }
        
    }
}
