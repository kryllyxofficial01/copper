#include "include/lexer.hpp"

Lexer::Lexer(std::string source) {
    this->source = source;

    this->index = -1;

    this->next_char();
}

std::vector<struct Token> Lexer::lex() {
    std::vector<struct Token> tokens;

    struct Token token;
    while ((token = this->get_next_token()).type != TT_EOF) {
        tokens.push_back(token);
    }

    return tokens;
}

struct Token Lexer::get_next_token() {
    while (this->index < this->source.size()) {
        if (__IS_ALNUM(this->current_char)) {
            return this->get_ID();
        }

        if (this->current_char == '"') {
            return this->get_string();
        }

        return this->get_char();
    }

    return (struct Token) {
        .type = TT_EOF,
        .value = "\0"
    };
}

struct Token Lexer::get_ID() {
    std::string value;
    while (__IS_ALNUM(this->current_char)) {
        value += this->current_char;
        this->next_char();
    }

    return (struct Token) {
        .type = TT_ID,
        .value = value
    };
}

struct Token Lexer::get_string() {
    this->next_char();

    std::string string;
    while (this->current_char != '"') {
        string += this->current_char;
        this->next_char();
    }

    this->next_char();

    return (struct Token) {
        .type = TT_STRING,
        .value = string
    };
}

struct Token Lexer::get_char() {
    switch (this->current_char) {
        case '(': return this->advance_with_token(
            (struct Token) {
                .type = TT_LEFT_PAREN,
                .value = "("
            }
        );

        case ')': return this->advance_with_token(
            (struct Token) {
                .type = TT_RIGHT_PAREN,
                .value = ")"
            }
        );

        case ';': return this->advance_with_token(
            (struct Token) {
                .type = TT_SEMICOLON,
                .value = ";"
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

struct Token Lexer::advance_with_token(struct Token token) {
    this->next_char();

    return token;
}

void Lexer::next_char() {
    this->current_char = this->source[
        ++this->index
    ];
}