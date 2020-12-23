
#ifndef CLIENTCONNECTION_HPP
#define CLIENTCONNECTION_HPP

#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include <Signature.grpc.pb.h>
#include <Version.grpc.pb.h>
#include <Login.grpc.pb.h>

using namespace delivery;
using namespace signature;
using namespace version;
using namespace login;

class ClientConnection
{
public:
    ClientConnection();
    static ClientConnection *instance();
    
    bool signatureValid(const std::string &signature);
    VersionResponse_Status versionValid(int major, int minor, int patch);
    std::string login(const std::string &username, const std::string &password);

private:
    std::unique_ptr<DeliverySignature::Stub> m_stubSignature;
    std::unique_ptr<DeliveryVersion::Stub> m_stubVersion;
    std::unique_ptr<DeliveryLogin::Stub> m_stubLogin;
};

#endif
