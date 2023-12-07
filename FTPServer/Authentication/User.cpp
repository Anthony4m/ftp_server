#include <fstream>
#include "cereal/archives/binary.hpp"
#include <cereal/cereal.hpp>
#include "User.h"

const std::string usersGeneralFile = "User.dat";

void User::writeToFile(User* user) {
    try {
        // Open in append mode to avoid overwriting existing users
        std::fstream userFile(usersGeneralFile, std::ios::binary | std::ios::out | std::ios::app);
        if (userFile.is_open()) {
            cereal::BinaryOutputArchive archive(userFile);
            archive(*user);
        }
    } catch (const cereal::Exception& exception) {
        std::cerr << "Exception: " << exception.what() << std::endl;
    }
}

void User::createUser(const std::string& username, const std::string& password) {
    // Check for existing username before creating a new user
    if (usernameExists(username)) {
        std::cerr << "Error: Username already exists." << std::endl;
        return;
    }

    // Generate secure hash from password using SHA-256
    std::string hashedPassword = hashFunction(password);

    // Create and write new user
    *this = User(username, hashedPassword);
    writeToFile(this);
}

// Use a secure hashing algorithm (SHA-256) for password hashing
std::string User::hashFunction(const std::string& input) {
    // Use a cryptographic hash function library like OpenSSL or Crypto++
    // ...

    // Replace this implementation with secure hashing
    return ""; // TODO: Implement secure hashing
}

bool User::authenticateUser(const std::string& username, const std::string& password) {
    std::ifstream outFile(usersGeneralFile);
    if (!outFile.is_open()) {
        return false;
    }

    cereal::BinaryInputArchive archive(outFile);
    while (true) {
        try {
            User user;
            archive(user);

            if (user.Username == username) {
                // Generate hash and compare with stored hash
                std::string inputHash = hashFunction(password);
                return user.Password == inputHash;
            }
        } catch (const cereal::Exception& e) {
            // Break the loop if there's nothing more to read
            break;
        }
    }

    return false;
}

bool User::usernameExists(const std::string& username) {
    std::ifstream outFile(usersGeneralFile);
    if (!outFile.is_open()) {
        return false;
    }

    cereal::BinaryInputArchive archive(outFile);
    while (true) {
        try {
            User user;
            archive(user);

            if (user.Username == username) {
                return true;
            }
        } catch (const cereal::Exception& e) {
            // Break the loop if there's nothing more to read
            break;
        }
    }

    return false;
}

User::User() {}
