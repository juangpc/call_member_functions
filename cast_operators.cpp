
//https://godbolt.org/#g:!((g:!((g:!((h:codeEditor,i:(fontScale:14,fontUsePx:'0',j:1,lang:c%2B%2B,selection:(endColumn:2,endLineNumber:26,positionColumn:1,positionLineNumber:1,selectionStartColumn:2,selectionStartLineNumber:26,startColumn:1,startLineNumber:1),source:'%23include+%3Ciostream%3E%0A%0Aclass+Pepe+%0A%7B%0Apublic:%0A++++Pepe(int+a):+_a%7Ba%7D+%7B+%7D%0A%0A++++operator+int()%0A++++%7B%0A++++++++return+33%3B%0A++++%7D%0Aprivate:+%0A++++int+_a%3B%0A%7D%3B%0A%0A%0Aint+main()%0A%7B%0A++++Pepe+p%7B3%7D%3B%0A%0A++++int+a+%3D+p%3B%0A%0A++++std::cout+%3C%3C+%22Hello+Pepe+:+%22+%3C%3C+a+%3C%3C+%22%5Cn%22%3B%0A%0A++++return+0%3B%0A%7D'),l:'5',n:'0',o:'C%2B%2B+source+%231',t:'0')),k:32.803409829927936,l:'4',m:100,n:'0',o:'',s:0,t:'0'),(g:!((h:executor,i:(argsPanelShown:'1',compilationPanelShown:'0',compiler:gsnapshot,compilerOutShown:'0',execArgs:'',execStdin:'',fontScale:14,fontUsePx:'0',j:1,lang:c%2B%2B,libs:!(),options:'',source:1,stdinPanelShown:'1',wrap:'1'),l:'5',n:'0',o:'x86-64+gcc+(trunk)+Executor+(Editor+%231)+C%2B%2B',t:'0')),header:(),k:67.19659017007207,l:'4',n:'0',o:'',s:0,t:'0')),l:'2',n:'0',o:'',t:'0')),version:4
#include <iostream>

class Pepe 
{
public:
    Pepe(int a): _a{a} { }

    operator int()
    {
        return 33;
    }
private: 
    int _a;
};


int main()
{
    Pepe p{3};

    int a = p;

    std::cout << "Hello Pepe : " << a << "\n";

    return 0;
}