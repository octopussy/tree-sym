#ifndef TREES_H
#define TREES_H

#include <string>

struct T2Node
{
    std::string value;
    T2Node* left;
    T2Node* right;
};

T2Node* parseT2(const std::string& input);

const auto tree01 = T2Node{
    .value = "root",
    .left = new T2Node{
        .value = "left",
        .left = new T2Node{
            .value = "l1",
        }
    },
    .right = new T2Node{
        .value = "asd",
        .right = new T2Node{
            .value = "asd",
        }
    },
};

const auto tree02 = T2Node{
    .value = "root",
    .left = new T2Node{
        .value = "add",
        .left = new T2Node{
            .value = "aasdj",
            .left = new T2Node{
                .value = "asd",
                .left = new T2Node{
                    .value = "add",
                },
            },
            .right = new T2Node {
                .value = "asd"
            }
        },
        .right = new T2Node{
            .value = "a",
            .left = new T2Node{
                .value = "asd",
                .right = new T2Node{
                    .value = "dds",
                    .left = new T2Node{
                        .value = "add",
                    },
                }
            },
            }
    },
    .right = new T2Node{
        .value = "q",
        .left = new T2Node{
            .value = "ff",
        },
        .right = new T2Node{
            .value = "ff",
            .right = new T2Node{
                .value = "s",
                .right = new T2Node{
                    .value = "eer",
                },
            }
        }
    },
};

#endif //TREES_H
