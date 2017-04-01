#include <iostream>
#include <vector>
#include <fstream>
#include "TreeBuilder.h"

void printTree(TreeEntry* entry, std::ofstream& out, int indents) {
    for (int i = 0; i < indents; i++)
        out << "   ";
    out << entry->getDate() << " " << entry->getContent() << std::endl;

    if (entry->getChildren() == NULL)
        return;

    for (auto& i : *entry->getChildren()) {
        printTree(i, out, indents + 1);
    }
}

void printTree(TreeEntry* root, std::ofstream& out) {
    for (auto& i : *root->getChildren()) {
        printTree(i, out, 0);
    }
}


int main() {
    TreeBuilder treeBuilder;
    std::ofstream out;
    out.open("..//sampleoutput.txt");

    treeBuilder.build("..//sampleparsed.txt");

    printTree(treeBuilder.getRoot(), out);

    return 0;
}