#include <iostream>
#include <vector>
#include <fstream>
#include "TreeBuilder.h"

void printTree(TreeEntry* entry, int indents) {
    for (int i = 0; i < indents; i++)
        std::cout << " ";
    std::cout << entry->getDate() << " " << entry->getContent() << std::endl;

    if (entry->getChildren() == NULL)
        return;

    for (auto& i : *entry->getChildren()) {
        printTree(i, indents + 1);
    }
}

void printTree(TreeEntry* root) {
    for (auto& i : *root->getChildren()) {
        printTree(i, 0);
    }
}


int main() {
    TreeBuilder treeBuilder;

    treeBuilder.build("..//sampleparsed.txt");

    printTree(treeBuilder.getRoot());

    return 0;
}