#pragma once
#include "IRequestHandler.h"
#include "LoginManeger.h"
#include "RequestHandlerFactory.h"
#include <string>
class RequestHandlerFactory;
class LoginRequestHandler :
    public IRequestHandler
{
public:
    LoginRequestHandler(LoginManeger& loginManeger, RequestHandlerFactory& handlerFactory);
    ~LoginRequestHandler();
    virtual bool isRequestRelevant(RequestInfo info) override;
    virtual RequestResult handleRequest(RequestInfo info) override;
    
private:
    LoginManeger &m_loginManeger;
    RequestHandlerFactory &m_handlerFactory;
};

