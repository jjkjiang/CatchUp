//
// Created by Explo on 4/1/2017.
//

#include "../include/TreeFilterer.h"

TreeFilterer::TreeFilterer() {
    root = NULL;
    indentStr = "  ";
    startDate = Date();
    endDate = Date();
    showDate = true;
}

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
    out.str("");
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
    // if i ever go back to this code, fix this more
    // elegantly

    if (entry->hasFittingChild(startDate, endDate)) {
        for (int i = 0; i < indent; i++)
            out << indentStr;

        if (showDate && entry->getChildren() == NULL)
            out << "[" <<entry->getDate() << "] ";
        else if (showDate && entry->getChildren()->size() < 2)
            out << "[" <<entry->getDate() << "] ";
        out << entry->getContent() << std::endl;

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

/*
 * goal: filter() checks whether or not to print something based on if there exists a child that
 * is valid. So, we recursively go and search for something. This creates an issue of overlapping
 * subproblems, and we are doing extra work - so, we can try fixing this with dynamic programming.
 *
 */
void TreeFilterer::filterDP() {
    out.str("");
    out.clear();

    if (root == NULL)
        return;

    if (root->getChildren() == NULL)
        return;

    TreeEntry* memo = new TreeEntry("0", root->getDate());

    for (int i = 0; i < root->getChildren()->size(); i++) {
        memo->addChild(new TreeEntry("0", root->getChildren()->at(i)->getDate()));
        filterDP(root->getChildren()->at(i), 0, memo->getChildren()->at(i));
    }
}


void TreeFilterer::filterDP(TreeEntry *entry, int indent, TreeEntry *memo) {
    if (entry->hasFittingChildDP(startDate, endDate, memo)) {
        for (int i = 0; i < indent; i++)
            out << indentStr;

        if (showDate && entry->getChildren() == NULL)
            out << "[" <<entry->getDate() << "] ";
        else if (showDate && entry->getChildren()->size() < 2)
            out << "[" <<entry->getDate() << "] ";
        out << entry->getContent() << std::endl;

        if (entry->getChildren() == NULL)
            return;

        if (entry->getChildren()->size() != memo->getChildren()->size()) {
            std::cout << entry->getChildren()->size() << " " << memo->getChildren()->size() << std::endl;
            std::cout << "in item " << entry->getContent() << std::endl;

            throw std::runtime_error("wtf");
        }

        for (int i = 0; i < entry->getChildren()->size(); i++)
            filterDP(entry->getChildren()->at(i), indent + 1, memo->getChildren()->at(i));
    }
}