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

    ~TreeEntry() {
        if (children == NULL) {
            return;
        }

        for (int i = 0; i < children->size(); i++) {
            delete children->at(i);
        }

        delete children;
    }

    const std::string &getContent() const {
        return content;
    }

    void setContent(const std::string &content) {
        TreeEntry::content = content;
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

    bool hasFittingChildDP(Date startDate, Date endDate, TreeEntry* memo) {
        if (memo->getContent() == "1")
            return true;

        if (children == NULL && startDate < date && endDate > date) {
            memo->setContent("1");
            return true;
        }

        if (children == NULL)
            return false;

        if (memo->getChildren() == NULL) {
            for (auto& i : *children) {
                TreeEntry* nextMemo = new TreeEntry("0", i->getDate());
                memo->addChild(nextMemo);
            }
        }

        for (int i = 0; i < children->size(); i++) {
            if (children->at(i)->hasFittingChildDP(startDate, endDate, memo->getChildren()->at(i))) {
                memo->setContent("1");
                return true;
            }
        }

        return false;
    }
};


#endif //CATCHUP_TREEENTRY_H
