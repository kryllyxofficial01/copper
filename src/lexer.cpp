#include "include/lexer.hpp"

Lexer::Lexer(std::string lines) {
    this->lines = lines;

    this->index = -1;

    this->next_char();
}

std::vector<Token> Lexer::lex() {
    std::vector<Token> tokens;

    Token token;
    while ((token = this->get_next_token()).type != TT_EOF) {
        tokens.push_back(token);
    }
    tokens.push_back(token);

    return tokens;
}

Token Lexer::get_next_token() {
    while (this->index < this->lines.size()) {
        this->skip_whitespace();

        if (isdigit(this->current_char)) {
            return this->get_type_number();
        }
        else if (this->current_char == '\"') {
            return this->get_type_string();
        }
        else if (isalnum(this->current_char) || this->current_char == '_') {
            return this->get_type_id();
        }

        return this->get_single_char();
    }

    return (Token) {
        .type = TT_EOF,
        .value = "\0"
    };
}

Token Lexer::get_type_id() {
    std::string id;
    while (isalnum(this->current_char) || this->current_char == '_') {
        id += this->current_char;
        this->next_char();
    }

    return (Token) {
        .type = TT_ID,
        .value = id
    };
}

Token Lexer::get_type_number() {
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

    return (Token) {
        .type = decimal_count == 1 ? TT_FLOAT : TT_INT,
        .value = number
    };
}

Token Lexer::get_type_string() {
    this->next_char();

    std::string string;
    while (this->current_char != '\"') {
        string += this->current_char;

        this->next_char();
    }

    this->next_char();

    return (Token) {
        .type = TT_STRING,
        .value = string
    };
}

Token Lexer::get_single_char() {
    switch (this->current_char) {
        case '(': {
            this->next_char();

            return (Token) {
                .type = TT_LEFT_PAREN,
                .value = "("
            };
        }

        case ')': {
            this->next_char();

            return (Token) {
                .type = TT_RIGHT_PAREN,
                .value = ")"
            };
        }

        case '{': {
            this->next_char();

            return (Token) {
                .type = TT_LEFT_BRACE,
                .value = "{"
            };
        }

        case '}': {
            this->next_char();

            return (Token) {
                .type = TT_RIGHT_BRACE,
                .value = "}"
            };
        }

        case '=': {
            this->next_char();

            return (Token) {
                .type = TT_EQUALS_SIGN,
                .value = "="
            };
        }

        case '-': {
            this->next_char();

            if (this->current_char == '>') {
                this->next_char();

                return (Token) {
                    .type = TT_RIGHT_ARROW,
                    .value = "->"
                };
            }

            // add hyphen token
        }

        case ':': {
            this->next_char();

            return (Token) {
                .type = TT_COLON,
                .value = ":"
            };
        }

        case ',': {
            this->next_char();

            return (Token) {
                .type = TT_COMMA,
                .value = ","
            };
        }

        case ';': {
            this->next_char();

            return (Token) {
                .type = TT_EOL,
                .value = ";"
            };
        }
    }
}

void Lexer::next_char() {
    this->current_char = this->lines[++this->index];
}

void Lexer::skip_whitespace() {
    while (isspace(this->current_char)) {
        this->next_char();
    }
}