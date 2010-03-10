    const char pause_shell[]="\xb8\x1d\x00\x00\x00\xcd\x80";

    main(){
      int (*shell)();
      shell=pause_shell;
      shell();
    }

