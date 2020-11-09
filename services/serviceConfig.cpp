
#include <thread>

#include <grpcpp/grpcpp.h>
#include <grpc/support/log.h>

#include "serviceConfig/ServiceSignatureCall.hpp"
#include "serviceConfig/ServiceVersionCall.hpp"

using namespace delivery;
using namespace signature;
using namespace version;

class ServerImpl final
{
public:
    ~ServerImpl()
    {
        m_server->Shutdown();
        for (int index = 0; index < 2; index++) {
            m_cq[index]->Shutdown();
        }
    }

    void run()
    {
        std::string server_address("0.0.0.0:50051");
        grpc::ServerBuilder builder;
        builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

        builder.RegisterService(&m_signatureService);
        builder.RegisterService(&m_versionService);

        for (int index = 0; index < 2; index++) {
            m_cq.push_back(builder.AddCompletionQueue());
        }

        m_server = builder.BuildAndStart();
        std::cout << "Server listening on " << server_address << std::endl;

        std::thread handle_signature(handleSignature, &m_signatureService, &m_cq[0]);
        std::thread handle_version(handleVersion, &m_versionService, &m_cq[1]);

        handle_signature.join();
        handle_version.join();
    }

private:
    DeliverySignature::AsyncService m_signatureService;
    DeliveryVersion::AsyncService m_versionService;

    std::vector<std::unique_ptr<grpc::ServerCompletionQueue>> m_cq;

    std::unique_ptr<grpc::Server> m_server;
};

int main(int argc, char **argv)
{
    ServerImpl server;
    server.run();
    return 0;
}
