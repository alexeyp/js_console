//to build this use
//D:\v8    
//d:
//cd v8
//cl /EHsc /Iinclude ../js_console/jc.cpp v8.lib winmm.lib ws2_32.lib
//in Visual Studio 2005 Command Prompt

#include <v8.h>
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace v8;

int x = 1;
int y = 2;

//X
Handle<Value> XGetter(Local<String> property, const AccessorInfo& info) {
    return Integer::New(x);
}

void XSetter(Local<String> property, Local<Value> value, const AccessorInfo& info) {
    x = value->Int32Value();
}

//Y
Handle<Value> YGetter(Local<String> property, const AccessorInfo& info) {
    return Integer::New(y);
}

void YSetter(Local<String> property, Local<Value> value, const AccessorInfo& info) {
    y = value->Int32Value();
}

int main(int argc, char* argv[]) {
    std::string input;
    std::cout << "JavaScript Console Start\n";
    std::cout << "------------------------\n";

    // Create a stack-allocated handle scope.
    HandleScope handle_scope;

    Handle<ObjectTemplate> global_templ = ObjectTemplate::New();
    global_templ->SetAccessor(String::New("x"), XGetter, XSetter);
    global_templ->SetAccessor(String::New("y"), YGetter, YSetter);

    // Create a new context.
    Persistent<Context> context = Context::New(NULL, global_templ);

    // Enter the created context for compiling and
    // running the hello world script.
    Context::Scope context_scope(context);

    do {
        std::getline(std::cin, input);

        char * buffer;
        buffer = new char[input.length()+1];
        strcpy(buffer, input.c_str());

	    // Create a string containing the JavaScript source code.
        Handle<String> source = String::New(buffer);

        //String::AsciiValue asciiSource(source);
        //printf("Source: '%s'\n", *asciiSource);
        
        // Compile the source code.
	    Handle<Script> script = Script::Compile(source);

	    // Run the script to get the result.
	    Handle<Value> result = script->Run();

  	    // Convert the result to an ASCII string and print it.
	    String::AsciiValue asciiResult(result);
        //printf("Result: '%s'\n", *asciiResult);
        printf("%s\n", *asciiResult);
    } while (input.length()>0);

	// Dispose the persistent context.
    context.Dispose();
    
    std::cout << "------------------------\n";
    std::cout << "JavaScript Console Exit\n";
	
    return 0;
}