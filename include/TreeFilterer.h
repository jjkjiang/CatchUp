//
// Created by Explo on 4/1/2017.
//

#ifndef CATCHUP_TREEFILTERER_H
#define CATCHUP_TREEFILTERER_H

#include <iostream>
#include "TreeEntry.h"

class TreeFilterer {
private:
    TreeEntry* root;
    std::stringstream out;
    std::string indentStr;
    Date startDate;
    Date endDate;
    bool showDate;
public:
    TreeFilterer();
    TreeFilterer(TreeEntry* root, Date startDate, Date endDate);

    TreeEntry *getRoot() const;
    void setRoot(TreeEntry *root);

    const std::string &getIndentStr() const;
    void setIndentStr(const std::string &indentStr);

    const Date &getStartDate() const;
    void setStartDate(const Date &startDate);

    const Date &getEndDate() const;
    void setEndDate(const Date &endDate);

    bool isShowDate() const;
    void setShowDate(bool showDate);

    void filter();
    void filter(TreeEntry* entry, int indent);

    void filterDP();
    void filterDP(TreeEntry *entry, int indent, TreeEntry *memo);
    std::string getResult();
};


#endif //CATCHUP_TREEFILTERER_H
