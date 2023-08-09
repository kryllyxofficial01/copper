#include "include/lexer.hpp"

Lexer::Lexer(std::string source) {
    this->source = source;

    this->index = -1;

    this->next_char();
}

std::vector<token_t> Lexer::lex() {
    std::vector<token_t> tokens;

    token_t token;
    while ((token = this->get_next_token()).type != TT_EOF) {
        tokens.push_back(token);
    }
    tokens.push_back(token);

    return tokens;
}

token_t Lexer::get_next_token() {
    while (this->index < this->source.size()) {
        if (__IS_WHITESPACE(this->current_char)) {
            this->skip_whitespace();
        }

        if (__IS_ALNUM(this->current_char)) {
            return this->get_ID();
        }

        if (this->current_char == '"') {
            return this->get_string();
        }

        return this->get_char();
    }

    return (token_t) {
        .type = TT_EOF,
        .value = "\0"
    };
}

token_t Lexer::get_ID() {
    std::string value;
    while (__IS_ALNUM(this->current_char)) {
        value += this->current_char;
        this->next_char();
    }

    return (token_t) {
        .type = TT_ID,
        .value = value
    };
}

token_t Lexer::get_string() {
    this->next_char();

    std::string string;
    while (this->current_char != '"') {
        string += this->current_char;
        this->next_char();
    }

    this->next_char();

    return (token_t) {
        .type = TT_STRING,
        .value = string
    };
}

token_t Lexer::get_char() {
    switch (this->current_char) {
        case '(':
            return this->advance_with_token(
                (token_t) {
                    .type = TT_LEFT_PAREN,
                    .value = "("
                }
            );

        case ')':
            return this->advance_with_token(
                (token_t) {
                    .type = TT_RIGHT_PAREN,
                    .value = ")"
                }
            );

        case ';':
            return this->advance_with_token(
                (token_t) {
                    .type = TT_SEMICOLON,
                    .value = ";"
                }
            );

        case ':':
            if (this->peek(1) == '=') {
                this->next_char();

                return this->advance_with_token(
                    (token_t) {
                        .type = TT_ASSIGNMENT_OPERATOR,
                        .value = ":="
                    }
                );
            }

            return this->advance_with_token(
                (token_t) {
                    .type = TT_COLON,
                    .value = ":"
                }
            );

        case '=':
            return this->advance_with_token(
                (token_t) {
                    .type = TT_EQUALS_SIGN,
                    .value = "="
                }
            );

        case ',':
            return this->advance_with_token(
                (token_t) {
                    .type = TT_COMMA,
                    .value = ","
                }
            );

        default:
            printf(
                "Unknown character: '%c'\n",
                this->current_char
            );
            exit(0);
    }
}

token_t Lexer::advance_with_token(token_t token) {
    this->next_char();

    return token;
}

void Lexer::next_char() {
    this->current_char = this->source[
        ++this->index
    ];
}

char Lexer::peek(size_t offset) {
    return this->source[
        this->index + offset
    ];
}

void Lexer::skip_whitespace() {
    while (__IS_WHITESPACE(this->current_char)) {
        this->next_char();
    }
}