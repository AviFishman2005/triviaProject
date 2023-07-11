#include "LoginRequestHandler.h"


LoginRequestHandler::LoginRequestHandler(LoginManeger& login, RequestHandlerFactory& handlerFactory):
    m_loginManeger(login), m_handlerFactory(handlerFactory)
{
}


LoginRequestHandler::~LoginRequestHandler()
{  
}
/// <summary>
/// Return true if the message is a login message and false if it is not 
/// in order to prevent false submitions
/// </summary>
/// <param name="info"></param>
/// <returns></returns>
bool LoginRequestHandler::isRequestRelevant(RequestInfo info)
{
    
    return (MT_LOG_IN == info.id)||(MT_SIGN_UP == info.id);
}
/// <summary>
/// This function needs to return serialized message back with a handler that handles the client 
/// </summary>
/// <param name="info"></param>
/// <returns></returns>
RequestResult LoginRequestHandler::handleRequest(RequestInfo info)
{
    RequestResult result;
    LoginRequest loginR;
    SignupRequest signupR;
    bool managerResponse;
    if (isRequestRelevant(info))
    {
        switch (info.id)
        {
        case MT_LOG_IN:
            LoginResponse login;
            loginR = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);
            managerResponse = m_loginManeger.login(loginR.username,loginR.password);
            if (managerResponse)
            {
                login.status = OK;
                result.response = JsonRequestPacketSerializer::serializeResponse(login);
                result.newHandler = m_handlerFactory.createMenuRequestHandler(loginR.username);
            }
            else
            {
                login.status = FAIL;
                result.response = JsonRequestPacketSerializer::serializeResponse(login);
                result.newHandler = nullptr;
            }
            return result;
            break;
        case MT_SIGN_UP:
            SignupResponse signup;
            signup.status = 1;
            signupR = JsonRequestPacketDeserializer::deserializeSignupRequest(info.buffer);
            managerResponse = m_loginManeger.signup(signupR.username, signupR.password, signupR.email);
            if (managerResponse)
            {
                signup.status = OK;
                result.response = JsonRequestPacketSerializer::serializeResponse(signup);
                result.newHandler = m_handlerFactory.createMenuRequestHandler(signupR.username);
            }
            else
            {
                signup.status = FAIL;
                result.response = JsonRequestPacketSerializer::serializeResponse(signup);
                result.newHandler = nullptr;
            }
            return result;
            break;
        }

    }
    ErrorResponse error;
    error.message = "error: try again";
    result.response = JsonRequestPacketSerializer::serializeResponse(error);
    result.newHandler = m_handlerFactory.createLoginRequestHandler();
    return result;
}

