#include "composite.h"
#include <cctype>
#include <stdexcept>

using namespace std;

// VAŠ KOD
Component::Component(Component *parent) : mParent(parent) {}

Component::~Component()
{
    mParent = nullptr;
    free(mParent);
}

void Component::read(ifstream &in)
{
    string naslov = "=";
    string poglavlje = "==";
    //vector<string> lines;
    while (!in.eof())
    {
        char c;
        auto input = in.peek();
        if (input == EOF)
            return;
        //preskoci sve whitespaceve
        while (isspace(input))
        {
            in.get(c);
            input = in.peek();
        }
        if (input == EOF)
            return;

        if (input == '=')
        {
            in.get(c);
            input = in.peek();

            if (input == '=')
            {
                //dva znaka jednakosti zaredom
                //makni i taj sljedeci
                in.get(c);
                //prebaci na novi
                in.get(c);
                string chapter;
                getline(in, chapter);

                Ptr temp(new Chapter(chapter, this));
                mChildren.push_back(move(temp));
            }
            else
            {
                //samo jedan znak jednakosti
                in.get(c);
                string title;
                getline(in, title);
                Ptr temp(new Title(title, this));
                mChildren.push_back(move(temp));
            }
            mChildren.back()->read(in);
        }
        else
        {
            Ptr temp(new Paragraph(this));
            mChildren.push_back(move(temp));

            mChildren.back()->read(in);
        }
    }
}

void Component::accept(Visitor *v)
{
    for (auto iter = mChildren.begin(); iter != mChildren.end(); ++iter)
        (*iter)->accept(v);
}

Title::Title(string const &title, Component *parent) : Component(parent), mTitle(title) {}

void Title::read(ifstream &in)
{
    while (!in.eof())
    {
        char c;
        auto input = in.peek();
        if (input == EOF)
            return;
        //preskoci sve whitespaceve
        while (isspace(input))
        {
            in.get(c);
            input = in.peek();
        }
        if (input == EOF)
            return;

        if (input == '=')
        {
            in.get(c);
            input = in.peek();

            if (input == '=')
            {
                //dva znaka jednakosti zaredom
                //makni i taj sljedeci
                in.get(c);
                //prebaci na novi
                in.get(c);
                string chapter;
                getline(in, chapter);

                Ptr temp(new Chapter(chapter, this));
                mChildren.push_back(move(temp));
            }
            else
            {
                in.unget();
                return;
            }
            mChildren.back()->read(in);
        }
        else
        {
            Ptr temp(new Paragraph(this));
            mChildren.push_back(move(temp));

            mChildren.back()->read(in);
        }
    }
}

void Title::accept(Visitor *v)
{
    v->visitTitle(this);
    for (auto iter = mChildren.begin(); iter != mChildren.end(); ++iter)
        (*iter)->accept(v);
}

Chapter::Chapter(string const &sec, Component *parent) : Component(parent), mChapter(sec) {}

void Chapter::read(ifstream &in)
{
    while (!in.eof())
    {
        char c;
        auto input = in.peek();
        if (input == EOF)
            return;
        //preskoci sve whitespaceve
        while (isspace(input))
        {
            in.get(c);
            input = in.peek();
        }
        if (input == EOF)
            return;

        if (input == '=') //zavrsio poglavlje
            return;
        else
        {
            Ptr temp(new Paragraph(this));
            mChildren.push_back(move(temp));

            mChildren.back()->read(in);
        }
    }
}

void Chapter::accept(Visitor *v)
{
    v->visitChapter(this);
    for (auto iter = mChildren.begin(); iter != mChildren.end(); ++iter)
        (*iter)->accept(v);
}

Paragraph::Paragraph(Component *parent) : Component(parent) {}

void Paragraph::read(ifstream &in)
{
    string line;
    getline(in, line);

    //paragraf je sve dok ne naletim na praznu liniju ili do kraja teksta
    while (!(line.empty() || in.eof()))
    {
        mText += line;
        mText += '\n';
        getline(in, line);
    }

    return;
}

void Paragraph::accept(Visitor *v)
{
    v->visitParagraph(this);
}

void HTMLVisitor::visitTitle(Title *title)
{
    mHTMLText += "<h1>" + title->mTitle + "</h1>";
    mHTMLText += "\n";
}

void HTMLVisitor::visitChapter(Chapter *chapter)
{
    mHTMLText += "<h2>" + chapter->mChapter + "</h2>";
    mHTMLText += "\n";
}

void HTMLVisitor::visitParagraph(Paragraph *paragraph)
{
    //malo slozenija jer ima jos bold i kurziv
    //ljepse je odvojit u novi red <p> i na kraju </p>
    mHTMLText += "<p>\n";
    Iterator iter(paragraph->mText);

    for (iter.first(); !iter.isDone(); iter.next())
    {
        string current = iter.current();
        if (current.at(0) == '*')
        {
            mHTMLText += "<b>";
            if (current.at(current.size() - 1) == '*')
                mHTMLText += current.substr(1, current.size() - 2);
            else
                mHTMLText += current.substr(1, current.size() - 1);
        }
        else if (current.at(0) == '_')
        {
            mHTMLText += "<i>";
            if (current.at(current.size() - 1) == '_')
                mHTMLText += current.substr(1, current.size() - 2);
            else
                mHTMLText += current.substr(1, current.size() - 1);
        }
        else
        {
            if (current.at(current.size() - 1) == '*' || current.at(current.size() - 1) == '_')
                mHTMLText += current.substr(0, current.size() - 1);
            else
                mHTMLText += current;
        }
        if (current.at(current.size() - 1) == '*')
            mHTMLText += "</b>";
        if (current.at(current.size() - 1) == '_')
            mHTMLText += "</i>";
        if (current.at(0) != '\n')
            mHTMLText += " ";
    }
    mHTMLText += "\n</p>\n";
}

Iterator::Iterator(string const &text) : mInitialString(text), mCurrentPosition(0) {}

void Iterator::first()
{
    for (int i = 0; i < mInitialString.size(); i++)
    {
        if (!isspace(mInitialString.at(i)))
            mCurrent += mInitialString.at(i);
        else
        {
            if (mInitialString.at(i) == '\n')
                mCurrentPosition = i;
            else
                mCurrentPosition = i + 1;
            break;
        }
    }
}
void Iterator::next()
{
    mCurrent = "";

    for (int i = mCurrentPosition; i < mInitialString.size(); ++i)
    {
        if (!isspace(mInitialString.at(i)))
            mCurrent += mInitialString.at(i);
        else
        {
            if (mInitialString.at(i) == '\n')
            {
                if (i == mCurrentPosition)
                {
                    mCurrent += mInitialString.at(i);
                    mCurrentPosition = i + 1;
                }
                else
                    mCurrentPosition = i;
            }
            else
                mCurrentPosition = i + 1;
            break;
        }
    }
}

string Iterator::current()
{
    return mCurrent;
}

bool Iterator::isDone() const
{
    return mCurrentPosition >= mInitialString.size() ? 1 : 0;
}