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

            if (level == 0)
                if (isDate(currentLine))
                    currentDate = Date(currentLine);

            if (level > currentLevel) {
                // if we are increasing the level
                // add the current line as entry if not present or only leaf exists
                // dont change anything if matching entry that has children
                if (level - currentLevel != 1)
                    throw std::runtime_error("Error in file, level increased by more than 1");

                TreeEntry* temp = findMatch(*levelStack.top()->getChildren(), currentLine);

                // elif used here to prevent deferencing null ptr
                if (temp == NULL) {
                    temp = new TreeEntry(currentLine, currentDate);
                    levelStack.top()->addChild(temp);
                } else if (temp->getChildren() != 0) {
                    temp = new TreeEntry(currentLine, currentDate);
                    levelStack.top()->addChild(temp);
                }

                levelStack.push(temp);
                currentLevel = level;
            } else if (level == currentLevel) {
                levelStack.pop();

            } else {

            }
        }
    }
private:
    // checks whether or not the current line indicates a new date of format
    // [YYYY/MM/DD]. Very weak checking - assumes the file used is correct.
    bool isDate(const std::string& currentLine) {
        if (currentLine.at(0) != '[' || currentLine.at(11) != ']')
            return false;
        return true;
    }

    // uses the parsed file's '-' characters to indicate which "level" in the stack
    // we are at
    int countLevels(const std::string& currentLine) {
        char frontChar = currentLine.at(0);
        unsigned cnt = 0;
        while (frontChar == '-') {
            cnt++;
            frontChar = currentLine.at(cnt);
        }

        return cnt;
    }

    // looks through a child vector for a matching category, otherwise returns NULL to
    // indicate adding a new value is fine. A category is defined as having existing children.
    TreeEntry* findMatch(const std::vector<TreeEntry*>& children, std::string candidate) {
        for (auto& i : children)
            if (i->getContent() == candidate && !i->getChildren()->empty())
                return i;

        return NULL;
    }
};


#endif //CATCHUP_TREEBUILDER_H
