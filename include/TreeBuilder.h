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
        root = NULL;
    }

    void build(std::string filename) {
        delete root;
        root = new TreeEntry("", Date());

        std::fstream fs;
        fs.open(filename.c_str());

        if (!fs.is_open())
            throw std::runtime_error("Could not locate or open file!");

        std::string currentLine;
        std::stack<TreeEntry*> levelStack;
        levelStack.push(root);
        int level, currentLevel = -1;
        Date currentDate;

        while (getline(fs, currentLine)) {
            if (currentLine.empty() || currentLine == "-\n")
                continue;

            level = countLevels(currentLine);

            if (level == currentLine.size())
                continue;

            if (level == 0)
                if (isDate(currentLine)) {
                    currentDate = Date(currentLine.substr(1, 10));
                    continue;
                }

            if (level > currentLevel) {
                // if we are increasing the level
                // add the current line as entry if not present or only leaf exists
                // dont change anything if matching entry that has children
                if (level - currentLevel != 1)
                    throw std::runtime_error("Error in file, level increased by more than 1");
            } else if (level == currentLevel) {
                levelStack.pop();
            } else {
                int popcnt = currentLevel - level;
                for (int i = 0; i <= popcnt; i++)
                    levelStack.pop();
            }

            TreeEntry* temp = findMatch(levelStack.top(), currentLine);

            if (temp == NULL) {
                temp = new TreeEntry(currentLine.substr(level), currentDate);
                levelStack.top()->addChild(temp);
            }

            levelStack.push(temp);
            currentLevel = level;
        }
    }

    TreeEntry *getRoot() const {
        return root;
    }
private:
    // checks whether or not the current line indicates a new date of format
    // [YYYY/MM/DD]. Very weak checking - assumes the file used is correct.
    bool isDate(const std::string& currentLine) {
        if (currentLine.empty())
            throw std::runtime_error("empty string");

        if (currentLine.at(0) != '[')
            return false;
        return true;
    }

    // uses the parsed file's '-' characters to indicate which "level" in the stack
    // we are at
    int countLevels(const std::string& currentLine) {
        return currentLine.find_first_not_of('-');


        char frontChar = currentLine.at(0);
        unsigned cnt = 0;
        while (frontChar == '-') {
            cnt++;
            if (cnt != currentLine.size())
                frontChar = currentLine.at(cnt);
        }

        return cnt;
    }

    // looks through a child vector for a matching category, otherwise returns NULL to
    // indicate adding a new value is fine. A category is defined as having existing children.
    TreeEntry* findMatch(TreeEntry* entry, std::string candidate) {
        if (entry->getChildren() == NULL)
            return NULL;

        candidate = candidate.substr(candidate.find_first_not_of('-'));

        for (auto i : *entry->getChildren())
            if (i->getContent() == candidate) //&& i->getChildren() != NULL)
                return i;

        return NULL;
    }
};


#endif //CATCHUP_TREEBUILDER_H
