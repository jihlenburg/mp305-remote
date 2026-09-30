/* Address: ram:0005f8d4; name: FUN_ram_0005f8d4; body bytes: 110 */

void FUN_ram_0005f8d4(int param_1)

{
  int iVar1;
  
  gp = 0x20004000;
  *(undefined1 *)(param_1 + 0x30) = 0xff;
  *(undefined1 *)(param_1 + 0x22) = *(undefined1 *)(param_1 + 0x21);
  *(undefined1 *)(param_1 + 0x21) = 8;
  FUN_ram_0006219c();
  FUN_ram_0005f7e6(param_1);
  *(undefined4 *)(DAT_ram_20001eb0 + 0xc) = 0xd00f;
  iVar1 = DAT_ram_20001eb0;
  fence.i();
  *(undefined4 *)(DAT_ram_20001eb0 + 8) = 0x2000;
  DAT_ram_20001e98 = 0x80;
  *(undefined4 *)(iVar1 + 100) = 0xd12;
  *(undefined4 *)(iVar1 + 0xc) = 0xf00f;
  *(undefined1 *)(param_1 + 10) = 0xa4;
  return;
}

