/* this is our special banner file ;> */

struct pussy {
    char *version, *log;
};
struct pussy banner_22[] = {
    {"SSH-1.5-1.2.24", "ssh_vuln.log"},	/* x2, 7350sshd */
    {"SSH-1.5-1.2.25", "ssh_vuln.log"},
    {"SSH-1.5-1.2.26", "ssh_vuln.log"},
    {"SSH-1.5-1.2.27", "ssh_vuln.log"},
    {"SSH-1.5-1.2.28", "ssh_vuln.log"},
    {"SSH-1.5-1.2.29", "ssh_vuln.log"},
    {"SSH-1.5-1.2.30", "ssh_vuln.log"},
    {"SSH-1.5-1.2.31", "ssh_vuln.log"},
    {"SSH-1.5-OpenSSH-1.2.1", "ssh_vuln.log"},
    {"SSH-1.5-OpenSSH-1.2.2", "ssh_vuln.log"},
    {"SSH-1.5-OpenSSH-1.2.3", "ssh_vuln.log"},
    {"SSH-1.5-OpenSSH-1.2", "ssh_vuln.log"},
    {"SSH-1.99-OpenSSH_2.1.1", "ssh_vuln.log"},
    {"SSH-1.99-OpenSSH-2.1", "ssh_vuln.log"},
    {"SSH-1.99-OpenSSH_2.2.0p1", "ssh_vuln.log"},
    {"SSH-1.99-OpenSSH_2.2.0", "ssh_vuln.log"},
/*    {"SSH-1.99-OpenSSH_2.9.9p2", "ssh_vuln.log"}, */ /* only for testing..heh */

    /* this versions are only affected with version 1 fallback
       { "SSH-1.99-2.0.11", "ssh_vuln.log" },
       { "SSH-1.99-2.0.12", "ssh_vuln.log" },
       { "SSH-1.99-2.0.13", "ssh_vuln.log" },
       { "SSH-1.99-2.1.0.pl2", "ssh_vuln.log" },
       { "SSH-1.99-2.1.0", "ssh_vuln.log" },
       { "SSH-1.99-2.2.0", "ssh_vuln.log" },
       { "SSH-1.99-2.3.0", "ssh_vuln.log" },
       { "SSH-1.99-2.4.0", "ssh_vuln.log" },
       { "SSH-1.99-3.0.0", "ssh_vuln.log" },
       { "SSH-1.99-3.0.1", "ssh_vuln.log" },
       { "SSH-2.0-2.3.0", "ssh_vuln.log" },
       { "SSH-2.0-2.4.0", "ssh_vuln.log" },
       { "SSH-2.0-3.0.0", "ssh_vuln.log" },
       { "SSH-2.0-3.0.1", "ssh_vuln.log" },
     */
    {NULL, NULL}
};
struct pussy banner_21[] = {
    {"Wed Aug 9 05:54:50 EDT 2000", "redhat7.log"},	/* seclpd, woot-exploit */
    {"wu-2.6.0(1) Mon Feb 28 10:30:36 EST 2000", "redhat62.log"},	/* too many.. */
    {"wu-2.6.1-18", "redhat72.log"},	/* woot-exploit... */
    {"FTP server (Version 6.00LS)", "freebsd.log"},	/* 7350bsd etc. */
    {"wu-", "wu-ftpd.log"},	/* wtf */
    {"ProFTPD 1.2.0pre4", "proftp.log"},
    {"ProFTPD 1.2.0pre3", "proftp.log"},
    {"ProFTPD 1.2.0pre2", "proftp.log"},
    {"ProFTPD 1.2.0pre1 Server", "proftp.log"},
    {"SunOS", "solaris.log"},	/* the rpc nightmare.. */
    {NULL, NULL}
};
struct pussy banner_23[] = {
    {"WinGate>", "wingate.log"},	/* could be handy :) */
    {NULL, NULL}
};
