#ifndef __TYPE_NODE_HPP
#define __TYPE_NODE_HPP

#include <string>

class IntegerNode {
    public:
        IntegerNode(int value) {
            this->value = value;
        }

        int value;
};

class FloatNode {
    public:
        FloatNode(double value) {
            this->value = value;
        }

        double value;
};

class StringNode {
    public:
        StringNode(std::string value) {
            this->value = value;
        }

        std::string value;
};

#endif