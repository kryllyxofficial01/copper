#include "include/lexer.hpp"

Lexer::Lexer(std::string line) {
    this->line = line;

    this->index = 0;

    this->next_char();
}

std::vector<token_t> Lexer::lex() {
    std::vector<token_t> tokens;

    token_t token;
    while ((token = this->get_next_token()).type != TT_EOL) {
        tokens.push_back(token);
    }
    tokens.push_back(token);

    return tokens;
}

token_t Lexer::get_next_token() {
    this->skip_whitespace();

    if (isdigit(this->current_char)) {
        return this->get_type_number();
    }
    else if (this->current_char == '\"') {
        return this->get_type_string();
    }
    else if (this->current_char == '\'') {
        return this->get_type_char();
    }
    else if (isalnum(this->current_char) || this->current_char == '_') {
        return this->get_type_id();
    }
    else {
        return this->get_single_char();
    }
}

token_t Lexer::get_type_id() {
    token_t token;

    std::string id;
    while (isalnum(this->current_char) || this->current_char == '_') {
        id += this->current_char;
        this->next_char();
    }

    token.type = TT_ID;
    token.value = id;

    return token;
}

token_t Lexer::get_type_number() {
    token_t token;

    std::string number;
    int decimal_count = 0;
    while (isdigit(this->current_char) || this->current_char == '.') {
        if (this->current_char == '.') {
            decimal_count++;
        }

        number += this->current_char;

        this->next_char();
    }

    if (decimal_count > 1) {
        printf(
            "Only 1 decimal point permitted: '%s'\n",
            number.c_str()
        );

        exit(EXIT_FAILURE);
    }

    token.type = decimal_count == 1 ? TT_FLOAT : TT_INT;
    token.value = number;

    return token;
}

token_t Lexer::get_type_string() {
    token_t token;

    this->next_char();

    std::string string;
    while (this->current_char != '\"') {
        string += this->current_char;

        this->next_char();
    }

    this->next_char();

    token.type = TT_STRING;
    token.value = string;

    return token;
}

token_t Lexer::get_type_char() {
    token_t token;

    this->next_char();

    std::string character;
    while (this->current_char != '\'') {
        character += this->current_char;

        this->next_char();
    }

    this->next_char();

    if (character.length() > 1) {
        printf(
            "Character type can only contain one value: '%s'\n",
            character.c_str()
        );

        exit(EXIT_FAILURE);
    }

    token.type = TT_CHAR;
    token.value = character;

    return token;
}

token_t Lexer::get_single_char() {
    token_t token;

    switch (this->current_char) {
        case '(': {
            token.type = TT_LEFT_PAREN;
            token.value = "(";

            break;
        }

        case ')': {
            token.type = TT_RIGHT_PAREN;
            token.value = ")";

            break;
        }

        case '=': {
            token.type = TT_EQUALS_SIGN;
            token.value = "=";

            break;
        }

        case ':': {
            token.type = TT_COLON;
            token.value = ":";

            break;
        }

        case ';': {
            token.type = TT_EOL;
            token.value = ";";

            break;
        }
    }

    this->next_char();

    return token;
}

void Lexer::next_char() {
    if (this->index < this->line.size()) {
        this->current_char = this->line.at(this->index++);
    }
}

void Lexer::skip_whitespace() {
    while (isspace(this->current_char)) {
        this->next_char();
    }
}