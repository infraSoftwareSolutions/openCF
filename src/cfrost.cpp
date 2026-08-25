#include <filesystem>
#include <unordered_map>
#include <string>
#include <fstream>
#include <vector>
#include <queue>
#include "cfrost/structure.h"

namespace cfrost {
    namespace data {
        ocf::hash_map<ocf::str, ocf::str>  var_types;
        ocf::hash_map<ocf::str, ocf::str>  obj;
        ocf::hash_map<ocf::str, ocf::str>  func;
        ocf::hash_map<ocf::str, ocf::str>  prefix;
        const ocf::hash_map<ocf::str, ocf::str>  postfix{
            {"bool", "bl"},
            {"char", "ch"},
            {"short", "si16"},
            {"int", "si32"},
            {"long", "si64"},
            {"float", "f32"},
            {"double", "f64"},
            {"str", "chptr"},
            {"uint8_t", "ui8"},
            {"uint16_t", "ui16"},
            {"uint32_t", "ui32"},
            {"uint64_t", "ui64"},
            {"int8_t", "si8"},
            {"int16_t", "si16"},
            {"int32_t", "si32"},
            {"int64_t", "si64"},
            {"const", "co"}
        };
    }

    namespace tools {
        bool is_type(const ocf::str& command) noexcept {
            if(command == "bool") return true;
            else if(command == "char") return true;
            else if(command == "short") return true;
            else if(command == "int") return true;
            else if(command == "long") return true;
            else if(command == "float") return true;
            else if(command == "double") return true;
            else if(command == "str") return true;
            else if(command == "uint8_t") return true;
            else if(command == "uint16_t") return true;
            else if(command == "uint32_t") return true;
            else if(command == "uint64_t") return true;
            else if(command == "int8_t") return true;
            else if(command == "int16_t") return true;
            else if(command == "int32_t") return true;
            else if(command == "int64_t") return true;
            else if(command == "const") return true;
            else return false;
        }
    }

    enum token_type {
        none,
        type,
        var,
        symbol,
        object,
        prefix,
        prefix_name,
        prefix_symbol,
        function,
        function_symbol,
        function_name,
        ignore
    };

    class token {
        private:
        ocf::str tok;
        char t;
        token_type type;
        public:
        token() = default;
        ~token() = default;
        token(const token & other) noexcept {
            this->tok = other.tok;
            this->t = other.t;
            this->type = other.type;
        }
        
        inline void operator=(const token& other) noexcept {
            this->tok = other.tok;
            this->t = other.t;
            this->type = other.type;
        }

        inline void operator=(const ocf::str& tok) noexcept { this->tok = tok; }
        inline void operator=(const char& t) noexcept { this->t = t; }
        inline void operator=(const token_type& type) noexcept { this->type = type; }

        inline bool operator==(const ocf::str& tok) noexcept { return this->tok == tok; }
        inline bool operator==(const char& t) noexcept { return this->t == t; }
        inline bool operator==(const token_type& type) noexcept { return this->type == type; }

        inline bool operator!=(const ocf::str& tok) noexcept { return this->tok != tok; }
        inline bool operator!=(const char& t) noexcept { return this->t != t; }
        inline bool operator!=(const token_type& type) noexcept { return this->type != type; }

        inline void operator<<(const char& tok) noexcept { this->tok += tok; }
        
        inline procedure(clear) noexcept {
            tok.clear();
            t = char();
            type = token_type::none;
        }
    };

    ocf::que<ocf::str> preformater(const std::filesystem::path& source) noexcept {
        for(const auto& entry : std::filesystem::directory_iterator(source)) {
            if(entry.is_directory()) preformater(entry.path());
            else if(entry.path().extension() == ".c") {
                std::ifstream file(entry.path());
                ocf::str command;
                ocf::que<ocf::str> formatted;
                while(std::getline(file, command)) {
                    if(command.empty()) continue;
                    else formatted.push(command);
                }
                file.close();
                return formatted;
            }
        }
    }

    ocf::que<ocf::que<token>> lexer(ocf::que<ocf::str>& source) noexcept {
        ocf::que<ocf::que<token>> result;
        while(!source.empty()) {
            ocf::que<token> temp_queue;
            token temp_token;
            bool is_new_name = false;
            ocf::str command = source.front(); source.pop();
            for(char c : command) {
                if( c == '(' ||
                    c == ')' ||
                    c == '{' ||
                    c == '}' ||
                    c == '[' ||
                    c == '=' ||
                    c == '!' ||
                    c == '-' ||
                    c == '+' ||
                    c == '/' ||
                    c == '*' ||
                    c == '&' ||
                    c == '|' ||
                    c == '\''||
                    c == '\"'||
                    c == ';'
                ) {
                    temp_token = c;
                    temp_token = token_type::symbol;
                } else if(c == ':') {
                    temp_token = c;
                    temp_token = token_type::prefix_symbol;
                } else if(temp_token == "func") {
                    temp_token = c;
                    temp_token = token_type::function;
                } else if(c != ' ') {
                    temp_token << c;
                    continue;
                }
                if(temp_token == "prefix") temp_token = token_type::prefix;
                else if(temp_token == "object") temp_token = token_type::object;
                temp_queue.push(temp_token);
                temp_token.clear();
            }
            result.push(temp_queue);
            temp_queue = ocf::que<token>();
        }
    }

    const ocf::que<ocf::str> formater(const ocf::que<token>& tokens) noexcept;
}

int main() {
    return 0;
}