#include "include/lexer.hpp"

Lexer::Lexer(std::string source) {
    this->source = source;
    this->index = 0;
    this->current_char = this->source[this->index];
};

std::vector<token_t> Lexer::lex() {
    std::vector<token_t> tokens;

    token_t token;
    while ((token = this->get_next_token()).type != EOF_TOKEN) {
        tokens.push_back(token);
    }
    tokens.push_back(token);

    return tokens;
}

token_t Lexer::get_next_token() {
    token_t token;

    while (this->index < this->source.size()) {
        if (strchr(WHITESPACE, this->current_char)) {
            this->skip_whitespace();
        }

        if (__IS_ALNUM(this->current_char)) {
            return this->get_ID();
        }
        else if (this->current_char == '"') {
            return this->get_string();
        }

        switch (this->current_char) {
            case '(':
                token.type = LEFT_PAREN_TOKEN;
                token.value = "(";

                break;

            case ')':
                token.type = RIGHT_PAREN_TOKEN;
                token.value = ")";

                break;

            case ';':
                token.type = SEMICOLON_TOKEN;
                token.value = ";";

                break;

            case ':':
                token.type = COMMA_TOKEN;
                token.value = ",";

                break;

            case '=':
                token.type = EQUALS_SIGN_TOKEN;
                token.value = "=";

                break;
        }

        return this->advance_with_token(token);
    }

    token.type = EOF_TOKEN;
    token.value = "\0";

    return token;
}

token_t Lexer::get_ID() {
    token_t id_token;

    std::string id = "";
    while (__IS_ALNUM(this->current_char)) {
        id += this->current_char;
        this->next_char();
    }

    id_token.type = ID_TOKEN;
    id_token.value = id;

    return id_token;
}

token_t Lexer::get_string() {
    this->next_char();

    token_t string_token;

    std::string string;
    while (this->current_char != '"') {
        string += this->current_char;
        this->next_char();
    }

    string_token.type = STRING_TOKEN;
    string_token.value = string;

    this->next_char();

    return string_token;
}

void Lexer::next_char() {
    if (this->index < this->source.size()) {
        this->index++;
        this->current_char = this->source[this->index];
    }
}

token_t Lexer::advance_with_token(token_t token) {
    this->next_char();

    return token;
}

void Lexer::skip_whitespace() {
    while (strchr(WHITESPACE, this->current_char)) {
        this->next_char();
    }
}