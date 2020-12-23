
#ifndef SERVICECONNECT_HPP
#define SERVICECONNECT_HPP

#include <grpcpp/grpcpp.h>
#include <grpc/support/log.h>

#include "serviceConnect/ServiceSignatureCall.hpp"
#include "serviceConnect/ServiceVersionCall.hpp"
#include "serviceConnect/ServiceLoginCall.hpp"

namespace delivery
{
    using namespace signature;
    using namespace version;
    using namespace login;

    namespace service
    {
        namespace config
        {

            class ConfigService final
            {
            public:
                ~ConfigService();
                void run();

            private:
                DeliverySignature::AsyncService m_signatureService;
                DeliveryVersion::AsyncService m_versionService;
                DeliveryLogin::AsyncService m_loginService;

                std::vector<std::unique_ptr<grpc::ServerCompletionQueue>> m_cq;

                std::unique_ptr<grpc::Server> m_server;
            };
        
        }   // namespace Config
    }       // namespace Service
}           // namespace Delivery

#endif  // SERVICECONNECT_HPP
