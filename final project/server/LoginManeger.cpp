#include "LoginManeger.h"


std::string LoggedUser::getUsername() const
{
    return this->m_username;
}

bool LoggedUser::isEqual(LoggedUser& other) const
{
    if (this->m_username == other.getUsername())
    {
        return true;
    }
    return false;
}

LoggedUser::LoggedUser(std::string username)
{
    this->m_username = username;
}

LoggedUser::LoggedUser()
{
}

LoggedUser::~LoggedUser()
{
}

bool LoggedUser::operator==(const LoggedUser& other) const
{
    return (this->m_username == other.getUsername());
}

//
//IDatabase* LoginManeger::m_database;
////LoginManeger::m_database = new IDatabase;
std::vector<LoggedUser> LoginManeger::m_loggedUsers;//because a static member needs decleration


LoginManeger::LoginManeger()
{
}

void LoginManeger::setDatabase(IDatabase* database)
{
    this->m_database = database;
}

LoginManeger::~LoginManeger()
{
}

bool LoginManeger::signup(std::string username, std::string password, std::string email)
{
    if (!m_database->doesUserExist(username))//if no same username
    {
        if (password.size() > 7)//check size
        {
            bool letter = false, notLetter = false;
            for (int i = 0; i < password.size(); i++)
            {
                if (isalpha(password[i]))
                {
                    letter = true;
                }
                else
                {
                    notLetter = true;
                }
                if (letter && notLetter)
                {
                    m_database->addNewUser(username, password, email);//add to db
                    LoggedUser user(username);//create loggedUser for vector of active users
                    m_loggedUsers.push_back(user);
                    this->m_database->updateStatistics(username, 0, 0, 0, 0, 0.0);//add to statisitcs table

                    return true;
                }
            }
        }
    }
    return false;
}

bool LoginManeger::login(std::string username, std::string password)
{
    if (m_database->doesPasswordMatch(username, password))
    {
        for (auto it = m_loggedUsers.begin(); it != m_loggedUsers.end(); it++)
        {
            if (it->getUsername() == username)
            {
                return false;
            }
        }
        LoggedUser user(username);//create loggedUser for vector of active users
        m_loggedUsers.push_back(user);
        return true;
    }
    return false;
}

void LoginManeger::logout(std::string username)
{
    LoggedUser user(username);
    std::vector<LoggedUser> users = m_loggedUsers;
    for (auto it = m_loggedUsers.begin(); it != m_loggedUsers.end(); it++)
    {
        if (it->getUsername() == username)
        {
            m_loggedUsers.erase(it);
            break;
        }
    }
}
