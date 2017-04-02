//
// Created by Explo on 4/1/2017.
//

#include "TreeFilterer.h"

TreeFilterer::TreeFilterer(TreeEntry* root, Date startDate, Date endDate) {
    this->root = root;
    indentStr = "  ";
    this->startDate = startDate;
    this->endDate = endDate;
    showDate = true;
    out.str("");
}

TreeEntry *TreeFilterer::getRoot() const {
    return root;
}

void TreeFilterer::setRoot(TreeEntry *root) {
    TreeFilterer::root = root;
}

const std::string &TreeFilterer::getIndentStr() const {
    return indentStr;
}

void TreeFilterer::setIndentStr(const std::string &indentStr) {
    TreeFilterer::indentStr = indentStr;
}

const Date &TreeFilterer::getStartDate() const {
    return startDate;
}

void TreeFilterer::setStartDate(const Date &startDate) {
    TreeFilterer::startDate = startDate;
}

const Date &TreeFilterer::getEndDate() const {
    return endDate;
}

void TreeFilterer::setEndDate(const Date &endDate) {
    TreeFilterer::endDate = endDate;
}

bool TreeFilterer::isShowDate() const {
    return showDate;
}

void TreeFilterer::setShowDate(bool showDate) {
    TreeFilterer::showDate = showDate;
}

void TreeFilterer::filter() {
    out.str("");\
    out.clear();

    // different if statements to prevent dereferencing null ptrs
    if (root == NULL)
        return;

    if (root->getChildren() == NULL)
        return;

    for (auto& i : *root->getChildren()) {
        filter(i, 0);
    }
}

void TreeFilterer::filter(TreeEntry* entry, int indent) {
    if (startDate < entry->getDate() && endDate > entry->getDate()) {
        for (int i = 0; i < indent; i++)
            out << indentStr;

        if (showDate)
            out << "[" <<entry->getDate() << "] ";
        out << entry->getContent();


        // when you use auto for loops to save work but
        // actually maybe do more figuring out whats wrong
        if (entry->getChildren() == NULL)
            return;

        for (auto& i : *entry->getChildren()) {
            filter(i, indent + 1);
        }
    }
}

std::string TreeFilterer::getResult() {
    return out.str();
}