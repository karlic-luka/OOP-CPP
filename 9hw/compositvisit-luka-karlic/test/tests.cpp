#include "gtest/gtest.h"
#include <string> 
#include "../src/composite.h"
#include <fstream>
#include <stdexcept>

 
using namespace std;

TEST(composite, text) {
    string fname{"12345.txt"};
    ofstream out(fname);
    if(!out)
        throw runtime_error("Cannot open file " + fname+".");

    out << "qwe rtz uio\n";
    out.close();
    ifstream in(fname);
    Component document;

    document.read(in);
    in.close();
    HTMLVisitor html;
    document.accept(&html);
    ASSERT_STREQ(html.getResult().c_str(),  "<p>\nqwe rtz uio \n</p>\n");
}

TEST(composite, title) {
    string fname{"12346.txt"};
    ofstream out(fname);
    if(!out)
        throw runtime_error("Cannot open file " + fname+".");

    out << "= Title\n";
    out.close();
    ifstream in(fname);
    Component document;

    document.read(in);
    in.close();
    HTMLVisitor html;
    document.accept(&html);
    ASSERT_STREQ(html.getResult().c_str(), "<h1>Title</h1>\n");
}

TEST(composite, chapter) {
    string fname{"12347.txt"};
    ofstream out(fname);
    if(!out)
        throw runtime_error("Cannot open file " + fname+".");

    out << "== Title\n";
    out.close();
    ifstream in(fname);
    Component document;

    document.read(in);
    in.close();
    HTMLVisitor html;
    document.accept(&html);
    ASSERT_STREQ(html.getResult().c_str(), "<h2>Title</h2>\n");
}

TEST(composite,titleChapter) {
    string fname{"12348.txt"};
    ofstream out(fname);
    if(!out)
        throw runtime_error("Cannot open file " + fname+".");

    out << "= Title\n== Chapter\n";
    out.close();
    ifstream in(fname);
    Component document;

    document.read(in);
    in.close();
    HTMLVisitor html;
    document.accept(&html);
    ASSERT_STREQ(html.getResult().c_str(), "<h1>Title</h1>\n<h2>Chapter</h2>\n");
}

