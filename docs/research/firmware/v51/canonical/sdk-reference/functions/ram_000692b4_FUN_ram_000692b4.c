/* Address: ram:000692b4; name: FUN_ram_000692b4; body bytes: 78 */

int FUN_ram_000692b4(uint param_1,int param_2)

{
  int iVar1;
  undefined1 auStack_20 [20];
  
  gp = 0x20004000;
  iVar1 = 2;
  if (((param_1 < DAT_ram_20001a8d) && (param_2 != 0)) &&
     (iVar1 = tmos_snv_read(param_1 * 6 + 0x20 & 0xfe,0x10,auStack_20), iVar1 == 0)) {
    tmos_memcpy(param_2,auStack_20,6);
  }
  return iVar1;
}

