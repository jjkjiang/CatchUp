//
// Created by Explo on 4/1/2017.
//

#ifndef CATCHUP_TREEBUILDER_H
#define CATCHUP_TREEBUILDER_H

#include <fstream>
#include <stdexcept>
#include <stack>
#include "TreeEntry.h"

class TreeBuilder {
private:
    TreeEntry* root;
public:
    TreeBuilder() {
        root = new TreeEntry("", Date());
    }
    void build(std::string filename) {
        std::fstream fs;
        fs.open(filename.c_str());

        if (!fs.is_open())
            throw std::runtime_error("Could not locate or open file!");

        std::string currentLine;
        std::stack<TreeEntry*> levelStack;
        levelStack.push(root);
        int level, currentLevel = -1;
        Date currentDate;

        // if theres no children and its a repeat, add it anyways

        while (getline(fs, currentLine)) {
            level = countLevels(currentLine);

            

            if (level > currentLevel) {
                //levelStack.push
                if (level - currentLevel != 1)
                    throw std::runtime_error("Error in file, level increased by more than 1");


            } else if (level == currentLevel) {

            } else {

            }
        }
    }
private:
    int countLevels(const std::string& currentLine) {
        char frontChar = currentLine.at(0);
        unsigned cnt = 0;
        while (frontChar == '-') {
            cnt++;
            frontChar = currentLine.at(cnt);
        }

        return cnt;
    }

    TreeEntry* findMatch(const std::vector<TreeEntry*> children, std::string candidate) {
        for (auto& i : children)
            if (i->getContent() == candidate)
                return i;

        return NULL;
    }
};


#endif //CATCHUP_TREEBUILDER_H
