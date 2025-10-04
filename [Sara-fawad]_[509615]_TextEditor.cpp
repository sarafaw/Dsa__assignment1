#include "TextEditor.h"
#include <iostream>
#include <list>
#include <string>

class LinkedListTextEditor : public TextEditor {
private:
    std::list<char> text;                 
    std::list<char>::iterator cursor;     
public:
    LinkedListTextEditor() {
        cursor = text.begin();           
    }
    void insertChar(char c) override {
        text.insert(cursor, c);
    }
    void deleteChar() override {
        if (cursor != text.begin()) {
            auto temp = cursor;
            --temp;
            text.erase(temp);
        }
    }
    void moveLeft() override {
        if (cursor != text.begin())
            --cursor;
    }
    void moveRight() override {
        if (cursor != text.end())
            ++cursor;
    }
      std::string getTextWithCursor()const override{
        std::string result;
        for (auto it = text.begin();it != text.end(); ++it) {
            if (it == cursor) result += "|";
            result += *it;
        }
        if (cursor == text.end()) result += "|"; 
        return result;

      }
};
TextEditor* createTextEditor(){
    return new LinkedListTextEditor();
}
