#include <iostream>
#include <vector>
using namespace std;

class IntefaceComponent{
    protected:
        string name;
        static int indent;
    public:
        string getName(){
            return name;
        }
        // to show directories
        virtual void ls() = 0;
};

// initializing indent to give proper indentation
int IntefaceComponent::indent = 0;

class File : public IntefaceComponent{
    public:
        File(string n){
            name = n;
        }
        void ls(){
            for(int i=0; i<indent; i++){
                cout<<" ";
            }
            cout<<"\033[32m"<<name<<"\033[0m"<<endl;
        }
};

class Folder : public IntefaceComponent{
    public:
        vector<IntefaceComponent*> dirs;
    public:
        Folder(string n){
            name = n;
        }
        void ls(){
            for(int i=0; i<indent; i++){
                cout<<" ";
            }
            indent += 5;
            cout<<"\033[31m"<<name<<"\033[0m"<<endl;
            for(int i=0; i<dirs.size(); i++){
                dirs[i]->ls();
            }
            indent -= 5;
        }
};

class Menu : public Folder{
    public:
        Menu(string s): Folder(s){}

        void addDir(IntefaceComponent* dir){
            dirs.emplace_back(dir);
        }
        void addFile(string n){
            addDir(new File(n));
        }
        void addFolder(string n){
            addDir(new Folder(n));
        }
        
        Menu* getHandle(string dir){
            for(int i=0; i<dirs.size(); i++){
                if(dirs[i]->getName() == dir){
                    return (Menu*)dirs[i];
                }
            }
            return nullptr;
        }

        void remove(string dir){
            vector<IntefaceComponent*>::iterator ptr = dirs.begin();
            for(int i=0; i<dirs.size(); i++){
                if(dirs[i]->getName() == dir){
                    dirs.erase(ptr);
                }
                ptr++;
            }
        }
};

int main(){
    Menu m("Main Folder");
    m.addFolder("First");
    m.getHandle("First")->addFile("First Folder File");
    m.getHandle("First")->addFile("First Folder File");
    m.getHandle("First")->addFolder("Inside First Folder");
    m.getHandle("First")->getHandle("Inside First Folder")->addFile("Inside First Folder File");

    m.addFolder("Second");
    m.getHandle("Second")->addFile("Second Folder File");
    m.getHandle("Second")->addFile("Second Folder File");

    // printing directories of Main Folder
    m.ls();

    // cout<<endl;
    // m.getHandle("First")->ls();
    // cout<<endl;
    //  m.getHandle("Second")->ls();
    return 0;
}