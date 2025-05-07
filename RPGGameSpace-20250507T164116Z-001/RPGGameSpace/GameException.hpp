#include <exception>
#include <string>
using namespace std;

class GameException : public exception {
public:
    explicit GameException(const std::string& message) : msg(message) {}
    const char* what() const noexcept override { return msg.c_str(); }
private:
    string msg;
};

class InvalidActionException : public GameException {
public:
    explicit InvalidActionException(const std::string& action)
        : GameException("Invalid action: " + action) {}
};
