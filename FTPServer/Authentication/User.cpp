//
// Created by pepos on 11/29/2023.
//
#include <fstream>
#include "cereal/archives/binary.hpp"
#include <cereal/cereal.hpp>
#include "User.h"
const std::string usersGeneralFile = "User.dat";
void User::writeToFile(User *user) {
    try {
        std::fstream userFile(usersGeneralFile, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate);
        if (userFile.is_open()) {
            cereal::BinaryOutputArchive archive(userFile);
            archive(*user);
        }
    }catch (cereal::Exception exception){
        std::cerr<<"Exception: " <<exception.what();
    }
}

void User::createUser(const std::string &username, const std::string &password) {
    *this = User(username, hashFunction(password));
    writeToFile(this);
}



std::string User::hashFunction(const std::string &input) {
    std::string ciphertext;
     std::string key = input + input;
    for (std::size_t i = 0; i < input.size(); ++i) {
        ciphertext += input[i] ^ key[i % key.size()];
    }
    return ciphertext;
}
std::string User::decrypt(const std::string &ciphertext) {
    return  User::hashFunction(ciphertext);
}

bool User::authenticateUser(const std::string &username, const std::string &password) {
    std::ifstream outFile(usersGeneralFile);
    if(outFile.is_open()){

        cereal::BinaryInputArchive archive(outFile);
        while (true){
            try {
                User user;
                archive(user);
                if (user.Username == username){
                    std::string file_password = user.decrypt(password);
                    if (user.Password == file_password){
                        return true;
                    }
                }
            } catch (const cereal::Exception &e) {
                // Break the loop if there's nothing more to read
                break;
            }
        }

    }
    return false;
}

User::User() {

}





