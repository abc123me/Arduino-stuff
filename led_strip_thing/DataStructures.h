struct Command{
    public:
    String* cmdName;
    StringArray* params;
    Command(String name, StringArray pars){
        cmdName = &name;
        params = &pars;
    }
};
/*struct StringArray{
    private:
    String mainStr = "";
    int length = 0;
    public:
    void AppendString(String s){
        mainStr += ((char) 0);
        mainStr += s;
    }
    String RemoveLast(){
        for(int i = mainStr.length(); i >= 0; i--){
            if(mainStr.charAt(i) == 0){
                return mainStr.substring(i, mainStr.length());
            }
        }
        return null;
    }
}*/
