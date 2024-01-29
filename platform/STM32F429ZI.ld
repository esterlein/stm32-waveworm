MEMORY
{
	rom (rx)  : ORIGIN = 0x08000000, LENGTH = 2048K
 	ccm (rwx) : ORIGIN = 0x10000000, LENGTH = 64K
	ram (rwx) : ORIGIN = 0x20000000, LENGTH = 192K
}

INCLUDE platform/Cortex-M.ld