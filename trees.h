//
// Created by user on 8/11/2025.
//

#ifndef TREES_H
#define TREES_H

struct Node
{
    int value;
    Node* left;
    Node* right;
};

const auto tree01 = Node{
    .value = 0,
    .left = new Node{
        .value = 1,
        .left = new Node{
            .value = 2,
        }
    },
    .right = new Node{
        .value = 1,
        .right = new Node{
            .value = 2,
        }
    },
};

const auto tree02 = Node{
    .value = 0,
    .left = new Node{
        .value = 1,
        .left = new Node{
            .value = 2,
            .left = new Node{
                .value = 3,
                .left = new Node{
                    .value = 72,
                },
            },
            .right = new Node {
                .value = 2
            }
        },
        .right = new Node{
            .value = 2,
            .left = new Node{
                .value = 2,
                .right = new Node{
                    .value = 3,
                    .left = new Node{
                        .value = 72,
                    },
                }
            },
            }
    },
    .right = new Node{
        .value = 1,
        .left = new Node{
            .value = 2,
        },
        .right = new Node{
            .value = 2,
            .right = new Node{
                .value = 3,
                .right = new Node{
                    .value = 72,
                },
            }
        }
    },
};

#endif //TREES_H
