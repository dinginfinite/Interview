#include "ini_parser.h"

#include <string.h>
#include <assert.h>
#include <iostream>

void test1()
{
    const char* ini_text= "a=1\nb=2\n";
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "\n", "=")) {
        assert(false);
    }

    const std::string& a = parser.Get("a", NULL);
    assert(a == "1");

    std::string b = parser.Get("b", NULL);
    assert(b == "2");

    const std::string& c = parser.Get("c", NULL);
    assert(c == "");
}

void test2()
{
    const char* ini_text= "a=1||b=2||c=3";
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "||", "=")) {
        assert(false);
    }

    const std::string& a = parser.Get("a", NULL);
    assert(a == "1");

    std::string b = parser.Get("b", NULL);
    assert(b == "2");

    const std::string& c = parser.Get("c", NULL);
    assert(c == "3");
}

void test3()
{
    const char* ini_text= "||||a:1||b:2||||c:3||||||";
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "||", ":")) {
        assert(false);
    }

    const std::string& a = parser.Get("a", NULL);
    assert(a == "1");

    std::string b = parser.Get("b", NULL);
    assert(b == "2");

    const std::string& c = parser.Get("c", NULL);
    assert(c == "3");
}

/* read from file */
void test4() {
  qh::INIParser parser;
  if (!parser.Parse("example.ini")) {
      assert(false);
  }

  const std::string& a = parser.Get("a", NULL);
  assert(a == "1");

  std::string b = parser.Get("b", NULL);
  assert(b == "222");

  const std::string& c = parser.Get("c", NULL);
  assert(c == "3");

  assert(parser.Get("section1", "a", NULL) == "22");
  assert(parser.Get("section1", "b", NULL) == "2345 ");
  assert(parser.Get("section1", "c", NULL) == " \"str\"");
  assert(parser.Get("section1", "d", NULL) == "4321");
  assert(parser.Get("section2", "a", NULL) == ";");
  assert(parser.Get("section2", "b", NULL) == ";");
  assert(parser.Get("section3", "s1", NULL) == "'");
  assert(parser.Get("section3", "s2", NULL) == "");
  assert(parser.Get("section3", "s3", NULL) == "'");
  assert(parser.Get("section3", "s4", NULL) == "''");
  assert(parser.Get("section3", "m1", NULL) == "\"");
  assert(parser.Get("section3", "m2", NULL) == "'");
}

void test5() {
    //odd "|", should be considered as bad key
    const char* ini_text= "||||a:1||b:2||||c:3|||||||";
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "||", ":")) {
        assert(true);
    }

    const std::string& a = parser.Get("a", NULL);
    assert(a == "1");

    std::string b = parser.Get("b", NULL);
    assert(b == "2");

    const std::string& c = parser.Get("c", NULL);
    assert(c == "3");
}

void test6() {
    //blanks
    const char* ini_text= "    ||  ||a:1||b:2||||c:3|||||||";
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "||", ":")) {
        assert(true);
    }

    const std::string& a = parser.Get("a", NULL);
    assert(a == "1");

    std::string b = parser.Get("b", NULL);
    assert(b == "2");

    const std::string& c = parser.Get("c", NULL);
    assert(c == "3");
}

void test7() {
    // null pointer
    const char* ini_text= "";
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "||", ":")) {
        assert(true);
    }

    const std::string& a = parser.Get("a", NULL);
    assert(a == "");
}

void test8() {
    // all blanks
    const char* ini_text= "     ";
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "||", ":")) {
        assert(true);
    }

    const std::string& a = parser.Get("a", NULL);
    assert(a == "");
}

void test9() {
    // no key-value
    const char* ini_text= "  ||   ";
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "||", ":")) {
        assert(true);
    }

    const std::string& a = parser.Get("a", NULL);
    assert(a == "");
}

void test10() {
    // only one pair
    const char* ini_text= "a:1";
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "||", ":")) {
        assert(true);
    }

    const std::string& a = parser.Get("a", NULL);
    assert(a == "1");
}

int main(int argc, char* argv[])
{
    //TODO 在这里添加单元测试，越多越好，代码路径覆盖率越全越好

    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();

    return 0;
}
