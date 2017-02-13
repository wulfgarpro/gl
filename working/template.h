#ifndef TEMPLATE_H
#define TEMPLATE_H

class Template {
    public:
        ~Template();

        virtual void display();
        virtual void init();

        virtual void setDrawCallback();
        static void drawCallback();
};

#endif  // TEMPLATE_H
