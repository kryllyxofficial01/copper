#include "include/lexer.hpp"

Lexer::Lexer(std::string source) {
    this->source = source;
    this->index = 0;
    this->current_char = this->source[this->index];
};

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

token_t Lexer::get_next_token() {
    token_t token;

    while (this->index < this->source.size()) {
        if (strchr(WHITESPACE, this->current_char)) {
            this->skip_whitespace();
        }

        if (isalnum(this->current_char)) {
            return this->get_ID();
        }
        else if (this->current_char == '"') {
            return this->get_string();
        }

        switch (this->current_char) {
            case '(':
                token.type = TOKEN_LEFT_PAREN;
                token.value = "(";

                return this->advance_with_token(token);

            case ')':
                token.type = TOKEN_RIGHT_PAREN;
                token.value = ")";

                return this->advance_with_token(token);

            case ';':
                token.type = TOKEN_SEMICOLON;
                token.value = ";";

                return this->advance_with_token(token);
        }
    }

    token.type = TOKEN_EOF;
    token.value = "\0";

    return token;
}

token_t Lexer::get_ID() {
    token_t id_token;

    std::string id = "";
    while (isalnum(this->current_char)) {
        id += this->current_char;
        this->next_char();
    }

    id_token.type = TOKEN_ID;
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

    string_token.type = TOKEN_STRING;
    string_token.value = string;

    this->next_char();

    return string_token;
}

void Lexer::skip_whitespace() {
    while (strchr(WHITESPACE, this->current_char)) {
        this->next_char();
    }
}