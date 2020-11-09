
#include "ServiceVersionCall.hpp"
#include <deliveryVersion.h>

namespace delivery
{
    namespace version
    {
        VersionCall::VersionCall(DeliveryVersion::AsyncService *service, grpc::ServerCompletionQueue *queue)
            : m_service(service)
            , m_queue(queue)
            , m_responder(&m_context)
            , m_status(CREATE)
        {
            process();
        }
        
        void VersionCall::process()
        {
            if (m_status == CREATE) {
                m_status = PROCESS;
                m_service->RequestVersion(&m_context, &m_request, &m_responder, m_queue, m_queue, this);
            } else if (m_status == PROCESS) {
                new VersionCall(m_service, m_queue);

                m_response.set_major(VERSION_MAJOR);
                m_response.set_minor(VERSION_MINOR);
                m_response.set_patch(VERSION_PATCH);
                m_response.set_status(VersionResponse_Status_VERSION_COMPATIBLE);

                m_status = FINISH;
                m_responder.Finish(m_response, grpc::Status::OK, this);
            } else {
                GPR_ASSERT(m_status == FINISH);
                delete this;
            }
        }

        void handleVersion(DeliveryVersion::AsyncService *service, std::unique_ptr<grpc::ServerCompletionQueue> *queue)
        {
            new VersionCall(service, queue->get());
            void *tag;
            bool ok;
            while (true) {
                GPR_ASSERT((*queue)->Next(&tag, &ok));
                GPR_ASSERT(&ok);
                static_cast<VersionCall*>(tag)->process();
            }
        }
        
    }
}
