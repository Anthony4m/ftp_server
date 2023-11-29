//
// Created by pepos on 11/29/2023.
//

#pragma once
#include <string>
#include "cereal/access.hpp"
#include <cereal/types/string.hpp>

class User{
    public:
    User();
    User(std::string Username,std::string Password):Username(Username),Password(Password){}

    // Declare cereal serialization function as a friend
    friend class cereal::access;
    template <class Archive>
    void serialize(Archive &archive) {
        archive(Username,Password);
    }
    void createUser(const std::string& username, const std::string& password);
    bool authenticateUser(const std::string& username, const std::string& password);
private:
    std::string Username;
    std::string Password;
    std::string hashFunction(const std::string& input);
    std::string decrypt(const std::string& ciphertext);

};