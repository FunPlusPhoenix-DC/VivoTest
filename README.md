The first time i succeed in compiling the vivopay's files.

#can see the tasks.json to get the configuration of GCC compiler.



NOTICE FOR CHANGING:(Use visual studio code with entire c/cpp extensions."C/C++" || "C/C++ Extension Pack" || "C/C++ Runner" are necessary).

1. ../.vscode/c_cpp_properties.json was made by "ctrl+shift+p"->"C/C++ edit configuration(UI)".

In this section,make sure to choose the right compilerPath(gcc.exe is recommanded).Then input the includePath to contain your HEADERS.

The ".vscode" folder will be created with c_cpp_properties.json.



2. Then everyone can copy "launch.json" / "setting.json" / "tasks.json" to your .vscode folder.



3. Be careful,there are several important settings need to be changed.

Firstly, you need to add a new path in "C_Cpp_Runner.includePaths".If you don't want to change it,just create the folder "include" and make it in the 

same route.



Secondly,These are the most important settings !!! Pay attention to it plz.⭐⭐⭐⭐⭐

In "tasks.json","command": "D:/MinGw/MinGW_64/x86_64-7.3.0-release-win32-seh-rt_v5-rev0/mingw64/bin/gcc.exe" is the route of compiler.

{
"args" is set to compiler.This "args" is used to tell the compiler the things it do.It's  NECESSARY to 

change "-g","{file}" to "-g","${fileDirname}\\*.c" , please comfirm that your .c files are placed in the same folder.⭐⭐⭐⭐⭐

"-I","D:/VivoTest/Headers" is used to tell the compiler the route where you placed headers.⭐⭐⭐⭐⭐

"-L","D:/VivoTest/lib" is used to tell the compiler the route where you placed library or dll.⭐⭐⭐⭐⭐

At last you need to tell compiler to use the dlls.That's why "-llibAugustaHID" existed.

"-l"('L' lowercase) + "name of dll" is correct format to set.⭐⭐⭐⭐⭐
}

Above all , Here is an example.Everyone can try to compile it according to my expirence.