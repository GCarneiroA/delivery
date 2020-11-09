
#include <iostream>
#include <memory>
#include <string>

#include <deliveryVersion.h>

#include <grpcpp/grpcpp.h>

#include <Signature.grpc.pb.h>
#include <Version.grpc.pb.h>

using namespace delivery;
using namespace signature;
using namespace version;

class Client
{
public:
    Client(std::shared_ptr<grpc::Channel> channel)
        : m_stubSignature(DeliverySignature::NewStub(channel))
        , m_stubVersion(DeliveryVersion::NewStub(channel)) {}
    
    bool SignatureValid(const std::string &signature)
    {
        SignatureRequest sRequest;
        sRequest.set_signature(signature);

        SignatureResponse sResponse;
        grpc::ClientContext context;

        grpc::Status status = m_stubSignature->Signature(&context, sRequest, &sResponse);
        if (status.ok()) {
            return sResponse.signaturevalid();
        } else {
            std::cout << status.error_code() << ": " << status.error_message() << std::endl;
            return false;
        }
    }

    VersionResponse_Status Version(int major, int minor, int patch)
    {
        VersionRequest vRequest;
        vRequest.set_major(VERSION_MAJOR);
        vRequest.set_minor(VERSION_MINOR);
        vRequest.set_patch(VERSION_PATCH);

        VersionResponse vResponse;
        grpc::ClientContext context;

        grpc::Status status = m_stubVersion->Version(&context, vRequest, &vResponse);
        if (status.ok()) {
            return vResponse.status();
        } else {
            std::cout << status.error_code() << ": " << status.error_message() << std::endl;
            return VersionResponse_Status_RPC_FAILED;
        }
    }

private:
    std::unique_ptr<DeliverySignature::Stub> m_stubSignature;
    std::unique_ptr<DeliveryVersion::Stub> m_stubVersion;
};

int main(int argc, char **argv)
{
    std::string target_str("localhost:50051");
    Client sClient(grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));

    std::string sSignature("sig12xss92383");
    bool sValid = sClient.SignatureValid(sSignature);
    if (sValid) {
        std::cout << "Signature is valid!" << std::endl;
    } else {
        std::cout << "Signature is invalid!" << std::endl;
    }
    
    VersionResponse_Status status = sClient.Version(0, 0, 1);
    switch (status)
    {
        case VersionResponse_Status_VERSION_VALID:
        {
            std::cout << "Version VALID!" << std::endl;
            break;
        }
        case VersionResponse_Status_VERSION_COMPATIBLE:
        {
            std::cout << "Version COMPATIBLE!" << std::endl;
            break;
        }
        case VersionResponse_Status_VERSION_PATCH_CHANGED:
        {
            std::cout << "Version PATCH CHANGED!" << std::endl;
            break;
        }
        case VersionResponse_Status_VERSION_INCOMPATIBLE:
        {
            std::cout << "Version INCOMPATIBLE!" << std::endl;
            break;
        }
        case VersionResponse_Status_RPC_FAILED:
        {
            std::cout << "Version RPC FAILED!" << std::endl;
            break;
        }
    }

    return 0;
}
