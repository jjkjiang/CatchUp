//
// Created by Explo on 4/1/2017.
//

#ifndef CATCHUP_TREEENTRY_H
#define CATCHUP_TREEENTRY_H

#include <vector>
#include <string>
#include "Date.h"

class TreeEntry {
private:
    std::string content;
    Date date;
    std::vector<TreeEntry*>* children;
public:
    TreeEntry(const std::string &content, const Date &date)
            : content(content), date(date) {
        children = NULL;
    }

    const std::string &getContent() const {
        return content;
    }

    const Date &getDate() const {
        return date;
    }

    std::vector<TreeEntry*>* getChildren() const {
        return children;
    }

    void addChild(TreeEntry* child) {
        if (children == NULL)
            children = new std::vector<TreeEntry*>();

        children->push_back(child);
    }

    bool hasFittingChild(Date startDate, Date endDate) {
        if (children == NULL && startDate < date && endDate > date)
            return true;

        if (children == NULL)
            return false;

        for (auto& i : *children) {
            if (i->hasFittingChild(startDate, endDate))
                return true;
        }

        return false;
    }
};


#endif //CATCHUP_TREEENTRY_H