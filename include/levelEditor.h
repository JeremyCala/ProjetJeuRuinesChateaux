#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

class screener;

class levelEditor
{
public :
    bool createLevel(const screener &S, int numLevel) const;
    bool isvalidLevel(const screener &S) const;
    void saveLevel(int numLevel) const;
};

#endif // LEVELEDITOR_H