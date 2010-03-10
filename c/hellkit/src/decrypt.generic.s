# generic decryptor, -sc.

# after the decoder has been created the memory looks like this:
#
# <decoder-code>[first ring data][second ring data]
#
# the decoder code is the stuff in this .s file, which does the following:
# 1. xor the first ring with the second ring
# 2. if the first ring isn't fully decrypted yet, do the rest with the
#    second ring
#

.text
.align 4
.globl main
.type main,@function

main:		jmp	.getip

.decryptstub:	popl	%esi
.decrypt:	movl	%esi, %edi		# edi = first ring offset

		xorl	%ecx, %ecx		# ecx = length
		decw	%cx			# cx = 0xffff
		subw	$(0xffff - 0x15), %cx	# ecx = first ring length
#		subw	$0xffff-length, %cx	# ecx = first ring length

		addl	%ecx, %esi		# esi = second ring offset
		movl	%esi, %ebp
		movb	$2, %bl
#		movb	$xorloop-length, %bl	# bl = second ring length

.hunk:		lodsb				# get second ring byte
		xorb	%al, (%edi)		# xor them
		incl	%edi			# next target byte

		decb	%bl			# second ring loop ?
		jnz	.hunk			# no -> next

		movl	%ebp, %esi
		mov	$2, %bl
#		mov	$xorloop-length, %bl
		loop	.hunk

		jmp	.realcode
.getip:		call	.decryptstub
.realcode:

	# scrambled content goes here
	# followed by xor-string

