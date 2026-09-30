/* Address: ram:0005d03c; name: FUN_ram_0005d03c; body bytes: 44 */

undefined4 FUN_ram_0005d03c(void)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = DAT_ram_20001dd8;
  gp = 0x20004000;
  uVar2 = 2;
  if (DAT_ram_20001dd8 != 0) {
    thunk_FUN_ram_00051f28(*(undefined2 *)(DAT_ram_20001dd8 + 0xb2));
    *(undefined2 *)(iVar1 + 0xb2) = 0xff;
    uVar2 = 0;
  }
  return uVar2;
}

