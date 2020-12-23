
#include "ClientConnection.hpp"

#include <deliveryVersion.h>

ClientConnection::ClientConnection()
{
    std::string target_str("localhost:50051");
    std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials());
    m_stubSignature = DeliverySignature::NewStub(channel);
    m_stubVersion = DeliveryVersion::NewStub(channel);
    m_stubLogin = DeliveryLogin::NewStub(channel);
}

ClientConnection *ClientConnection::instance() 
{
    static ClientConnection *cConnection;
    if (!cConnection) {
        cConnection = new ClientConnection();
    }
    return cConnection;
}

bool ClientConnection::signatureValid(const std::string &signature)
{
    SignatureRequest sRequest;
    sRequest.set_signature(signature);

    SignatureResponse sResponse;
    grpc::ClientContext context;

    grpc::Status status = m_stubSignature->Signature(&context, sRequest, &sResponse);
    return status.ok() ? sResponse.signaturevalid() : false;
}

VersionResponse_Status ClientConnection::versionValid(int major, int minor, int patch)
{
    VersionRequest vRequest;
    vRequest.set_major(VERSION_MAJOR);
    vRequest.set_minor(VERSION_MINOR);
    vRequest.set_patch(VERSION_PATCH);

    VersionResponse vResponse;
    grpc::ClientContext context;

    grpc::Status status = m_stubVersion->Version(&context, vRequest, &vResponse);
    return status.ok() ? vResponse.status() : VersionResponse_Status_RPC_FAILED;
}

std::string ClientConnection::login(const std::string &username, const std::string &password, LoginResponse_Status loginStatus)
{
    LoginRequest lRequest;
    lRequest.set_username(username);
    lRequest.set_password(password);

    LoginResponse lResponse;
    grpc::ClientContext context;

    grpc::Status status = m_stubLogin->Login(&context, lRequest, &lResponse);
    loginStatus = lResponse.status();
    return status.ok() ? lResponse.token() : std::string();
}
